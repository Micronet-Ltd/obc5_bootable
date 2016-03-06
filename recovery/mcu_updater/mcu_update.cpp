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

#define MCU_UPD_REV     "REV"
#define MCU_UPD_STA     "STA"
#define MCU_UPD_STB     "STB"
#define MCU_UPD_RAB     "RAB"
#define MCU_UPD_ERA     "ERA"
#define MCU_UPD_ERB     "ERB"
#define MCU_UPD_PFD     "PFD"
#define MCU_UPD_OK      "OK"
#define MCU_UPD_ERR     "ERR"
#define MCU_UPD_nRDY    "nRDY"
#define MCU_UPD_AA      "AA"
#define MCU_UPD_BB      "BB"

#define MCU_UPD_LOG "/cache/mcu_ua.log"

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

char hex2ch(char *num)
{
    int digh, digl;
    digh = ('0' <= num[0] && num[0] <= '9') ? num[0] - '0':
           ('A' <= num[0] && num[0] <= 'F') ? num[0] - 'A' + 10:
           ('a' <= num[0] && num[0] <= 'f') ? num[0] - 'a' + 10:-1;
    if (digh < 0) {
        printf("mcu update[%s]: high not digit %c%c\n\n", __func__, num[0], num[1]); 
        return digh;
    }

    digl = ('0' <= num[1] && num[1] <= '9') ? num[1] - '0':
           ('A' <= num[1] && num[1] <= 'F') ? num[1] - 'A' + 10:
           ('a' <= num[1] && num[1] <= 'f') ? num[1] - 'a' + 10:-1;
    if (digl < 0) {
        printf("mcu update[%s]: low not digit %c%c\n\n", __func__, num[0], num[1]); 
        return digl;
    }

    return (digh << 4) | digl; 
}

int tx2mcu(int fd_tty, char *s_rec, int len)
{
    int xferd;
    //printf("mcu update[%s]: s-record %s\n", __func__, s_rec);

    tcflush(fd_tty, TCIOFLUSH);

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
        s_rec += xferd;
    } while (len); 

    return 0;
}

int mcu2rx(int fd_tty, char *buf, int len, int tout)
{
    int xferd;
    time_t timeout_time = gettime() + tout;

    do {
        if (-1 != tout) {
            if (gettime() > timeout_time)
                break;
        }

        xferd = read(fd_tty, buf, len);
        if (xferd < 0) {
            if (errno == EINTR || errno == EAGAIN) {
                continue;
            }
            printf("mcu update[%s]: failure xfer %s\n", __func__, strerror(errno)); 
            return -1;
        }
        len -= xferd;
        buf += xferd;
    } while (len); 

    return 0;
}

int mcu2srec_rx(int fd_tty, char *buf, int len, int tout)
{
    int xferd, err = -1;
    time_t timeout_time = gettime() + tout;
    char *r = buf;

    do {
        if (-1 != tout) {
            if (gettime() > timeout_time)
                break;
        }

        xferd = read(fd_tty, r, len);
        if (xferd < 0) {
            if (errno == EINTR || errno == EAGAIN) {
                continue;
            }
            printf("mcu update[%s]: failure xfer %s\n", __func__, strerror(errno)); 
            return -1;
        }
        len -= xferd;
        r += xferd;
        if (0 == strncmp(buf, MCU_UPD_nRDY, strlen(MCU_UPD_nRDY))) {
            err = 1;
            break;
        } else if (0 == strncmp(buf, MCU_UPD_ERR, strlen(MCU_UPD_ERR))) {
            err = -1;
            break;
        } else if (0 == strncmp(buf, MCU_UPD_OK, strlen(MCU_UPD_OK))) {
            err = 0;
            break;
        }
    } while (len); 

    return err;
}

// Vladimir:
// All timeouts set to ifinite for debugging purposes only
// TODO: set relevant timeouts values
//
int main(int argc, char **argv)
{
    int fd_tty, fd_done, err, i;
    FILE *fi;
    struct stat info;
    char const *mcu_update_got = "/tmp/.rb_mcu_update_got";
    char const *mcu_update_done = "/tmp/.rb_mcu_update_done";
    char const *mcu_binary = "/cache/mcu.bin";
    char const *tty_n = "/dev/ttyHSL0";
    char s_rec[64], resp[64], rev[32];
    time_t start = time(0);

    redirect_stdio(MCU_UPD_LOG);

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
        redirect_stdio("/dev/tty");
        return EXIT_FAILURE;
    }

    start = time(&start);
    printf("mcu update[%s]: got on %s\n", __func__, ctime(&start));

    fd_tty = open(tty_n, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_tty < 0) {
        printf("mcu update[%s]: %s failure to open terminal %s\n", __func__, tty_n, strerror(errno));
        fclose(fi);
        redirect_stdio("/dev/tty");
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
        ios.c_cc[VTIME] = 10;   /* unit: 1/10 second. */
        ios.c_cc[VMIN] = 1;     /* minimal characters for reading */

        tcsetattr( fd_tty, TCSANOW, &ios );
        tcflush(fd_tty,TCIOFLUSH);
    } else {
        printf("mcu update[%s]: %s invalid terminal %s\n", __func__, tty_n, strerror(errno));
        close(fd_tty);
        fclose(fi);
        redirect_stdio("/dev/tty");
        return EXIT_FAILURE;
    }

    do {
        // check version
        //
        if (0 != tx2mcu(fd_tty, (char *)MCU_UPD_REV, strlen(MCU_UPD_REV))) {
            printf("mcu update[%s]: %s failure to transmit rev cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        err = mcu2rx(fd_tty, resp, 8, -1);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on rev cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        resp[7] = 0;
        //if (0 == strncmp(resp, MCU_UPD_ERR, strlen(MCU_UPD_ERR))) {
        //    printf("mcu update[%s]: %s invalid rev cmd %s\n", __func__, tty_n, strerror(errno));
        //    break;
        //}

        if (!fgets(s_rec, sizeof(s_rec) - 1, fi)) {
            printf("mcu update[%s]: %s revision failure %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        s_rec[sizeof(s_rec) - 1] = 0;

        if ((err = pars_srec(s_rec, strlen(s_rec))) < 0 || S_REC_0 != err) {
            printf("mcu update[%s]: not s0-record %s\n", __func__, s_rec);
            break;
        }

        err = hex2ch(&s_rec[2]);
        if (err < 0) {
            printf("mcu update[%s]: %s invalid lenth of %s %s\n", __func__, s_rec, tty_n, strerror(errno));
            break;
        }

        err -= 3;           // 16-bit address "0000" and check sum
        i = (3 << 1) + 2;   // S0 and 16-bit address
        printf("mcu update[%s]: %s len %d\n", __func__, s_rec, err);
        while (err > 0) {
            int ch;
            if ((ch = hex2ch(&s_rec[i])) < 0) {
                printf("mcu update[%s]: %s not digit %d %s\n", __func__, &s_rec[i], i, strerror(errno));
                break;
            }
            printf(" %d", ch);
            s_rec[(i - 8)>>1] = ch; // 8 see above
            i += 2;
            err--;
        }
        printf("\n");
        if (err != 0) {
            break;
        }

        s_rec[(i - 8)>>1] = 0;
        if (0 != strncmp(resp, s_rec, strlen(resp))) {
            printf("mcu update[%s]: %s invalid version %s\n", __func__, resp, s_rec);
            // Vladimir:
            // temporary for debugging purposes only
            // TODO: proper version check
            //
            //break;
        }

        // check execution location, start address in flash (P Flash/FlashNVM)
        //
        if (0 != tx2mcu(fd_tty, (char *)MCU_UPD_RAB, strlen(MCU_UPD_RAB))) {
            printf("mcu update[%s]: %s failure to transmit execution location cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, 2, -1);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on execution location cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        resp[2] = 0;
        if (0 == strncmp(resp, MCU_UPD_AA, 2)) {
            strncpy(resp, MCU_UPD_STA, sizeof(MCU_UPD_STA));
            strncpy(s_rec, MCU_UPD_ERA, sizeof(MCU_UPD_ERA));
        } else if (0 == strncmp(resp, MCU_UPD_BB, 2)) {
            strncpy(resp, MCU_UPD_STB, sizeof(MCU_UPD_STB));
            strncpy(s_rec, MCU_UPD_ERB, sizeof(MCU_UPD_ERA));
        } else {
            printf("mcu update[%s]: invalid execution location %s\n", __func__, resp);
            break;
        }

        // tx start command
        //
        if (0 != tx2mcu(fd_tty, resp, strlen(resp))) {
            printf("mcu update[%s]: %s failure to start update cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, strlen(MCU_UPD_OK), -1);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on start update cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        if (0 != strncmp(resp, MCU_UPD_OK, strlen(MCU_UPD_OK))) {
            printf("mcu update[%s]: %s failure to start update %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        // tx erase command
        //
        if (0 != tx2mcu(fd_tty, s_rec, strlen(s_rec))) {
            printf("mcu update[%s]: %s failure to erase cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, strlen(MCU_UPD_OK), -1);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on erase cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        if (0 != strncmp(resp, MCU_UPD_OK, strlen(MCU_UPD_OK))) {
            printf("mcu update[%s]: %s failure to erase %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        while (fgets(s_rec, sizeof(s_rec) - 1, fi)) {
            s_rec[sizeof(s_rec) - 1] = 0;

            if ((err = pars_srec(s_rec, strlen(s_rec))) < 0) {
                printf("mcu update[%s]: not s-record %s\n", __func__, s_rec);
            }

            // skip all not relevant instructions
            if (S_REC_8 == err || S_REC_9 == err) {
                // Temporary don't tx reset instruction
                // tx2mcu(fd_tty, s_rec, strlen(s_rec)); 
            } else if (S_REC_1 == err || S_REC_2 == err) {
                do {
                    if (0 != tx2mcu(fd_tty, s_rec, strlen(s_rec))) {
                        printf("mcu update[%s]: %s failure to tx s-rec %s\n", __func__, tty_n, strerror(errno));
                        break;
                    }
                    memset(resp, 0, strlen(MCU_UPD_nRDY));
                    err = mcu2srec_rx(fd_tty, resp, strlen(MCU_UPD_nRDY), -1);
                    if (err < 0) {
                        printf("mcu update[%s]: mcu don't respond on tx s-rec %s\n", __func__, s_rec);
                    } else if (1 == err) {
                        printf("mcu update[%s]: mcu not ready\n", __func__);
                    }
                } while (1 == err);

                if (0 != err) {
                    printf("mcu update[%s]: failure\n", __func__);
                    break;
                }
            }
        }

        if (0 != tx2mcu(fd_tty, (char *)MCU_UPD_PFD, strlen(MCU_UPD_PFD))) {
            printf("mcu update[%s]: %s failure to transmit finish cmd %s\n", __func__, tty_n, strerror(errno));
        }
    } while (0);

    close(fd_tty);
    fclose(fi);
    fd_done = open(mcu_update_done, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    close(fd_done);
//    usleep(10000000);

    printf("Done\n");
    redirect_stdio("/dev/tty");

    return EXIT_SUCCESS;
} 
