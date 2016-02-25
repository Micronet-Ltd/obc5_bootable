/*
 * Copyright (C) 2016 Micronet Inc
 * <vladimir.zatulovsky@micronet-inc.com>
 * 
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <linux/input.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/klog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <termio.h>
#if 0
#include "bootloader.h"
#include "common.h"
#include "cutils/properties.h"
#include "cutils/android_reboot.h"
#include "install.h"
#include "minui/minui.h"
#include "minzip/DirUtil.h"
#include "roots.h"
#include "device.h"
#include "adb_install.h"
extern "C" {
#include "minadbd/adb.h"
#include "fuse_sideload.h"
#include "fuse_sdcard_provider.h"
}
#endif

static void redirect_stdio(const char* filename)
{
    // If these fail, there's not really anywhere to complain...
    freopen(filename, "a", stdout);
    setbuf(stdout, 0);
    freopen(filename, "a", stderr);
    setbuf(stderr, 0);
}

// close a file, log an error if the error indicator is set
static void check_and_fclose(FILE *fp, const char *name)
{
    fflush(fp);
    if (ferror(fp))
        printf("Error in %s\n(%s)\n", name, strerror(errno));
    fclose(fp);
}

static void print_property(const char *key, const char *name, void *cookie)
{
    printf("%s=%s\n", key, name);
}

static time_t gettime(void)
{
    struct timespec ts;
    int err;

    err = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (err < 0) {
        printf("clock_gettime(CLOCK_MONOTONIC) failed: %s\n", strerror(errno));
        return 0;
    }

    return ts.tv_sec;
}

static int wait_for_file(const char *filename, int timeout)
{
    struct stat info;
    time_t timeout_time = gettime() + timeout;
    int err = -1;

    do {
        err = stat(filename, &info);
        if (0 == err || errno != ENOENT) {
            err = 0;
            break;
        }

        if (-1 != timeout) {
            if (gettime() > timeout_time)
                break;
        }
        usleep(10000);
    } while (1); 

    return err;
}

#define S_REC_0 0
#define S_REC_1 1
#define S_REC_2 2
#define S_REC_3 3
#define S_REC_4 4
#define S_REC_5 5
#define S_REC_6 6
#define S_REC_7 7
#define S_REC_8 8
#define S_REC_9 9

int pars_srec(char *s_rec, int len)
{
    int s_rec_t = -1;

    if (!s_rec || len < 4) {
        return s_rec_t;
    }

    if ('S' != s_rec[0]) {
        return s_rec_t;
    }

    s_rec_t = s_rec[1] - '0';
    if (s_rec_t < S_REC_0 || s_rec_t > S_REC_9) {
        return -1;
    }

    s_rec += 2;
    len -= 2;
    do {
        if ('\r' == *s_rec && '\n' == *(s_rec + 1)) {
            *s_rec = 0;
            return s_rec_t;
        }
        s_rec ++;
        len --;
    } while (len > 1);

    return -1;
}

int tx2mcu(int fd_tty, char *s_rec, int len)
{
    int xferd;
    //printf("mcu update[%s]: s-record %s\n", __func__, s_rec);
    do {
        xferd = write(fd_tty, s_rec, len);
        if (xferd < 0) {
            if (errno == EINTR || errno == EAGAIN) {
                continue;
            }
            printf("mcu update[%s]: failure xfer %s\n\t%s\n", __func__, s_rec, strerror(errno)); 
            return -1;
        }
        len -= xferd;
    } while (len); 

    return 0;
}

int main(int argc, char **argv)
{
    int fd_tty, err;
    FILE *fi;
    struct stat info;
    char const *mcu_update_got = "/tmp/.rb_mcu_update_got";
    char const *mcu_update_done = "/tmp/.rb_mcu_update_done";
    char const *mcu_binary = "/cache/mcu.bin";
    char const *tty_n = "/dev/ttyHSL0";
    char s_rec[64];
    time_t start = time(0);

    //redirect_stdio("/dev/ttyHSL0");

    printf("mcu update[%s]: Starting (pid %d) on %s\n", __func__, getpid(), ctime(&start));

    err = wait_for_file(mcu_update_got, -1);
    if (0 != err) {
        start = time(&start);
        printf("mcu update[%s]: got doesn't exist %s\n", __func__, ctime(&start));
    }

    chmod(mcu_binary, S_IRUSR | S_IRGRP | S_IROTH);
    fi = fopen(mcu_binary, "r");
    if (!fi) {
        printf("mcu update[%s]: %s doesn't exist %s\n", __func__, mcu_binary, strerror(errno));
        return EXIT_FAILURE;
    }

    start = time(&start);
    printf("mcu update[%s]: got on %s\n", __func__, ctime(&start));

    fd_tty = open(tty_n, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_tty < 0) {
        printf("mcu update[%s]: %s failure to open terminal %s\n", __func__, tty_n, strerror(errno));
        fclose(fi);
        return EXIT_FAILURE;
    }

    if (isatty(fd_tty)) {
        struct termios  ios;

        tcgetattr(fd_tty, &ios);

        bzero(&ios, sizeof(ios));

        cfmakeraw(&ios);
        //ios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        //ios.c_oflag &= ~OPOST;
        //ios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        //ios.c_cflag &= ~(CSIZE | PARENB);
        //ios.c_cflag |= CS8;

        cfsetospeed(&ios, B115200);
        cfsetispeed(&ios, B115200);
        ios.c_cflag =  (B115200 | CS8 | CLOCAL | CREAD) & ~(CRTSCTS | CSTOPB | PARENB);
        ios.c_iflag = 0;
        ios.c_oflag = 0;
        ios.c_lflag = 0;        /* disable ECHO, ICANON, etc... */
        ios.c_cc[VTIME] = 1;    /* unit: 1/10 second. */
        ios.c_cc[VMIN] = 1;     /* minimal characters for reading */

        tcsetattr( fd_tty, TCSANOW, &ios );
        tcflush(fd_tty,TCIOFLUSH);
    } else {
        printf("mcu update[%s]: %s invalid terminal %s\n", __func__, tty_n, strerror(errno));
        close(fd_tty);
        fclose(fi);
        return EXIT_FAILURE;
    }
#if 0
fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd_tty, &readfds);
        /* Wait up to 100 ms. */
        tv.tv_sec = 0;
        tv.tv_usec = 100;
        ret = read( fd_tty, buf, sizeof(buf) );
            if (ret > 0) {
            }
#endif

    while (fgets(s_rec, sizeof(s_rec) - 1, fi)) {
        s_rec[sizeof(s_rec) - 1] = 0;

        if (pars_srec(s_rec, strlen(s_rec)) < 0) {
            printf("mcu update[%s]: not s-record %s\n", __func__, s_rec);
        }
        tx2mcu(fd_tty, s_rec, strlen(s_rec));
    }

    close(fd_tty);
    fclose(fi);
//    usleep(10000000);

    printf("Done\n");

    return EXIT_SUCCESS;
} 
