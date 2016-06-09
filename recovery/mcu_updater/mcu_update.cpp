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
#include "cutils/properties.h"

#if 0
#include "bootloader.h"
#include "common.h"
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
#define MCU_UPD_SPI_FLASH_PAGE_L 256
#define MCU_UPD_FPGA_REV         "FRE"
#define MCU_UPD_FPGA_STF         "STF"
#define MCU_UPD_FPGA_nCRC        "nCRC"

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

#define MCU_UPD_TX_TO   -1
#define MCU_UPD_RX_TO   4

#define MCU_UPD_LOG     "/cache/mcu_ua.log"
#define TTYHSL0_UPD_LOG "/dev/ttyHSL0"

#undef REDIRECT_STDIO
#define REDIRECT_STDIO MCU_UPD_LOG
//#define REDIRECT_STDIO TTYHSL0_UPD_LOG

#if defined (REDIRECT_STDIO)
static void redirect_stdio(const char* filename)
{
    // If these fail, there's not really anywhere to complain...
    freopen(filename, "a", stdout);
    setbuf(stdout, 0);
    freopen(filename, "a", stderr);
    setbuf(stderr, 0);
}
#endif

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
        if (0 == err) {
            printf("mcu update[%s]: %s found\n", __func__, filename);
            break;
        }

        if (errno == ENOENT) {
            //printf("mcu update[%s]: %s not found\n", __func__, filename);
        }

        if (-1 != timeout) {
            if (gettime() > timeout_time) {
                printf("mcu update[%s]: %s timeout\n", __func__, filename);
                break;
            }
        }
        usleep(10000);
    } while (1); 

    return err;
}

#if 0
static int check_rb_delta_exist(const char *filename, int timeout)
{
    struct stat info;
    time_t timeout_time = gettime() + timeout;
    int err = -1;

    do {
        err = stat(filename, &info);
        if (0 == err) {
            printf("mcu update[%s]: %s found\n", __func__, filename);
            break;
        }

        if (errno == ENOENT) {
           // printf("mcu update[%s]: %s not found\n", __func__, filename);
        }

        if (-1 != timeout) {
            if (gettime() > timeout_time) {
                printf("mcu update[%s]: %s time out\n", __func__, filename);
                break;
            }
        }
        usleep(10000);
    } while (1); 

    return err;
}
#endif

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

static int pars_srec(char *s_rec, int len)
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

static void num2hex(uint32_t n, char *hex)
{
    uint32_t mask = 0xF0000000, shift = 28;

    if (!hex) {
        return;
    }

    do {
        *hex++ = 0x30;
        *hex++ = (n & mask)>>shift;
        mask >>= 4;
        shift -= 4;
    } while (mask);
}

static char hex2ch(char *num)
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

static int tx2mcu(int fd_tty, uint8_t *s_rec, int len)
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

static int mcu2rx(int fd_tty, char *buf, int len, int tout)
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

static int mcu2srec_rx(int fd_tty, char *buf, int len, int tout)
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
        if (0 == strncmp(buf, MCU_UPD_FPGA_nCRC, strlen(MCU_UPD_FPGA_nCRC))) {
            err = 2;
            break;
        } else if (0 == strncmp(buf, MCU_UPD_nRDY, strlen(MCU_UPD_nRDY))) {
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

#define CRC32_POLINOMIAL 0xEDB88320
static uint32_t crc_32(uint8_t *page, int len) {
   int i, j;
   uint32_t crc, m;

   i = 0;
   crc = 0xFFFFFFFF;
   for (i = 0; i < len; i++) {
      crc = crc ^ (uint32_t)page[i];
      for (j = 7; j >= 0; j--) {    // Do eight times.
         m = -(crc & 1);
         crc = (crc >> 1) ^ (CRC32_POLINOMIAL & m);
      }
   }

   return ~crc;
}

static int fpga_need_for_update(FILE *f, const char *rev) {
    int rd;
    char b[128], *pb;
    time_t t_r, t_f;
    tm tm_r, tm_f;

    rd = fread(b, 1, 82, f);
    b[rd-1] = 0;
    if (rd != 82) {
        return 0;
    }

    if (0 != strncmp(&b[2], "Lattice", 7)) {
        return 0;
    }
    if (0 != strncmp(&b[31], "Part: iCE40HX4K-CB132", 21)) {
        return 0;
    }

    pb = strtok(b, "Date:");
    if (!pb) {
        return 0;
    }

    do {
        if (*pb != ' ')
            break;
    } while (*pb++);

    if (0 != *pb) {
        // Vladimir
        // TODO: real revision check
        //
        strptime(pb, "%b %d %Y %H:%M:%S", &tm_f);
        strptime(rev, "%b %d %Y %H:%M:%S", &tm_r);

        t_r = mktime(&tm_r);
        t_f = mktime(&tm_f);
        //if (difftime(t_f, t_r) < 0) {
            return 1;
        //}
#if 0
        rd = min(strlen(rev), strlen(pb))
        do {
            if (*rev++ < *pb++) {
                return 1;
            }
        } while (red--);
#endif
    }

    return 0;
}

// Vladimir:
// All timeouts set to ifinite for debugging purposes only
// TODO: set relevant timeouts values
//
int main(int argc, char **argv)
{
    int fd_tty, fd_done, err, i, fpga_update;
    FILE *fi;
    struct stat info;
    char const *mcu_update_got = "/tmp/.rb_mcu_update_got";
    char const *mcu_update_done = "/tmp/.rb_mcu_update_done";
    char const *mcu_binary = "/cache/mcu0.bin";
    char const *mcu_binary2 = "/cache/mcu1.bin";
    char const *fpga_binary = "/cache/fpga.bin";
//    char const *recovery_list = "/sdcard/recovery-list.txt";
    char *mcu_srec, *sta, *er;
    char const *tty_n = "/dev/ttyHSL1";
    char s_rec[64], resp[64], rev[32];
    uint8_t flash_page[260];
    time_t start = time(0);

#if defined (REDIRECT_STDIO)
    redirect_stdio(REDIRECT_STDIO);
#endif

    printf("mcu update[%s]: Starting (pid %d) on %s\n", __func__, getpid(), ctime(&start));
/*
    err = wait_for_file(recovery_list, 4);
    if (0 == err) {
        start = time(&start);
        printf("mcu update[%s]: recovery list exists %s\n", __func__, ctime(&start));
        mount("/dev/block/bootdevice/by-name/system", "/system", "ext4", MS_NOATIME | MS_NODEV | MS_NODIRATIME);
#if 0
        do {
            ;
        } while (1);
#endif
    }
*/
    err = wait_for_file("/sdcard/delta", 1);
    start = time(&start);
    if (0 == err) {
        printf("mcu update[%s]: sdcard zero delta %s\n", __func__, ctime(&start));
        property_set("rb_ua.dp.sdcard", "1");
    } else{
        printf("mcu update[%s]: regular delta %s\n", __func__, ctime(&start));
        property_set("rb_ua.dp.sdcard", "0");
    }

    printf("mcu update[%s]: wait for rb_ua %s\n", __func__, ctime(&start));
    err = wait_for_file(mcu_update_got, -1);
    start = time(&start);
    if (0 != err) {
        printf("mcu update[%s]: got doesn't exist %s\n", __func__, ctime(&start));
    }

    printf("mcu update[%s]: wait for mcu s-rec files %s\n", __func__, ctime(&start));
    err = wait_for_file(mcu_binary, 4); 
    if (0 == err) {
        chmod(mcu_binary, S_IRUSR | S_IRGRP | S_IROTH);
    }
    err = wait_for_file(mcu_binary2, 4); 
    if (0 == err) {
        chmod(mcu_binary2, S_IRUSR | S_IRGRP | S_IROTH);
    }

    start = time(&start);
    printf("mcu update[%s]: wait for FPGA binary %s\n", __func__, ctime(&start));
    fpga_update = 0;
    err = wait_for_file(fpga_binary, 4); 
    start = time(&start);
    if (0 == err) {
        err = stat(fpga_binary, &info);
        if (0 == err) {
            chmod(fpga_binary, S_IRUSR | S_IRGRP | S_IROTH);
            printf("mcu update[%s]: FPGA update is present %s\n", __func__, ctime(&start));
            fpga_update = 1;
        }
    }

    printf("mcu update[%s]: got on %s\n", __func__, ctime(&start));

    fd_tty = open(tty_n, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_tty < 0) {
        printf("mcu update[%s]: %s failure to open terminal %s\n", __func__, tty_n, strerror(errno));
#if defined (REDIRECT_STDIO)
        redirect_stdio("/dev/tty");
#endif
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
#if defined (REDIRECT_STDIO)
        redirect_stdio("/dev/tty");
#endif
        return EXIT_FAILURE;
    }

    do {
        fi = 0;
        // check fpga version
        //
        if (fpga_update) {
            if (0 != tx2mcu(fd_tty, (uint8_t *)MCU_UPD_FPGA_REV, strlen(MCU_UPD_FPGA_REV))) {
                printf("mcu update[%s]: %s failure to transmit fpga rev cmd %s\n", __func__, tty_n, strerror(errno));
                break;
            }

            err = mcu2rx(fd_tty, rev, 28, MCU_UPD_RX_TO);
            if (0 == err) {
                printf("mcu update[%s]: %s mcu support fpga rev cmd %s\n", __func__, tty_n, strerror(errno));
                rev[28] = 0;
                fi = fopen(fpga_binary, "r");
                if (fi) {
                    if (fpga_need_for_update(fi, rev)) {
                        //  fseek(fi, 0, SEEK_SET);
                        rewind(fi);

                        num2hex(info.st_size, rev);
                        rev[17] = 0;
                        sprintf(s_rec, "%s%s", MCU_UPD_FPGA_STF, rev);

                        // tx start command
                        //
                        printf("mcu update[%s]: start update [%s]\n", __func__, s_rec);
                        if (0 != tx2mcu(fd_tty, (uint8_t *)s_rec, strlen(s_rec)+1)) {
                            printf("mcu update[%s]: %s failure to start FPGA update cmd %s\n", __func__, tty_n, strerror(errno));
                            break;
                        }
                        err = mcu2rx(fd_tty, resp, strlen(MCU_UPD_OK), MCU_UPD_RX_TO);
                        if (0 != err) {
                            printf("mcu update[%s]: %s mcu don't respond on start FPGA update cmd %s\n", __func__, tty_n, strerror(errno));
                        } else {
                            do {
                                i = fread(flash_page, 1, MCU_UPD_SPI_FLASH_PAGE_L, fi); 
                                if (i) {
                                    uint32_t crc;

                                    //memset(&flash_page[i], 0, sizeof(flash_page) - i);
                                    //crc = crc_32(flash_page, MCU_UPD_SPI_FLASH_PAGE_L);
                                    crc = crc_32(flash_page, i);
                                    //flash_page[MCU_UPD_SPI_FLASH_PAGE_L]   = crc         & 0xFF;
                                    //flash_page[MCU_UPD_SPI_FLASH_PAGE_L+1] = (crc >>  8) & 0xFF;
                                    //flash_page[MCU_UPD_SPI_FLASH_PAGE_L+2] = (crc >> 16) & 0xFF;
                                    //flash_page[MCU_UPD_SPI_FLASH_PAGE_L+3] = (crc >> 24) & 0xFF;
                                    flash_page[i]   = crc         & 0xFF;
                                    flash_page[i+1] = (crc >>  8) & 0xFF;
                                    flash_page[i+2] = (crc >> 16) & 0xFF;
                                    flash_page[i+3] = (crc >> 24) & 0xFF;
                                    do {
                                        //err = tx2mcu(fd_tty, flash_page, sizeof(flash_page));
                                        err = tx2mcu(fd_tty, flash_page, i+4);
                                        if (0 != err) {
                                            printf("mcu update[%s]: %s failure to tx flash page %s\n", __func__, tty_n, strerror(errno));
                                            break;
                                        }
                                        memset(resp, 0, strlen(MCU_UPD_nRDY));
                                        err = mcu2srec_rx(fd_tty, resp, strlen(MCU_UPD_nRDY), MCU_UPD_RX_TO);
                                        if (err < 0) {
                                            printf("mcu update[%s]: mcu don't respond on tx flash page %s\n", __func__, s_rec);
                                        } else if (1 == err) {
                                            printf("mcu update[%s]: mcu not ready\n", __func__);
                                        } else if (2 == err) {
                                            printf("mcu update[%s]: CRC error\n", __func__);
                                        }
                                    } while (1 == err || 2 == err);

                                    if (0 != err) {
                                        break;
                                    }
                                }
                            } while (i == MCU_UPD_SPI_FLASH_PAGE_L);

                            printf("mcu update[%s]: signal about update done\n", __func__);
                            if (0 != tx2mcu(fd_tty, (uint8_t *)MCU_UPD_PFD, strlen(MCU_UPD_PFD))) {
                                printf("mcu update[%s]: %s failure to transmit finish cmd %s\n", __func__, tty_n, strerror(errno));
                            }
                        }
                    }
                    fclose(fi);
                } else {
                    printf("mcu update[%s]: %s doesn't exist %s\n", __func__, fpga_binary, strerror(errno));
                }
            } else {
                printf("mcu update[%s]: %s mcu doesn't support fpga rev cmd, SPI Flash won't updated %s\n", __func__, tty_n, strerror(errno));
            }
        }

        // check version
        //
        if (0 != tx2mcu(fd_tty, (uint8_t *)MCU_UPD_REV, strlen(MCU_UPD_REV))) {
            printf("mcu update[%s]: %s failure to transmit rev cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        err = mcu2rx(fd_tty, rev, 8, MCU_UPD_RX_TO);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on rev cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        rev[8] = 0;
        //if (0 == strncmp(resp, MCU_UPD_ERR, strlen(MCU_UPD_ERR))) {
        //    printf("mcu update[%s]: %s invalid rev cmd %s\n", __func__, tty_n, strerror(errno));
        //    break;
        //}

        // check execution location, start address in flash (P Flash/FlashNVM)
        //
        if (0 != tx2mcu(fd_tty, (uint8_t *)MCU_UPD_RAB, strlen(MCU_UPD_RAB))) {
            printf("mcu update[%s]: %s failure to transmit execution location cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, 2, MCU_UPD_RX_TO);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on execution location cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        resp[2] = 0;
        if (0 == strncmp(resp, MCU_UPD_BB, 2)) {
            sta = (char *)MCU_UPD_STA;
            er  = (char *)MCU_UPD_ERA;
            mcu_srec = (char *)mcu_binary;
        } else if (0 == strncmp(resp, MCU_UPD_AA, 2)) {
            sta = (char *)MCU_UPD_STB;
            er  = (char *)MCU_UPD_ERB;
            mcu_srec = (char *)mcu_binary2;
        } else {
            printf("mcu update[%s]: invalid execution location %s\n", __func__, resp);
            break;
        }

        fi = fopen(mcu_srec, "r");
        if (!fi) {
            printf("mcu update[%s]: %s doesn't exist %s\n", __func__, mcu_srec, strerror(errno));
            break;
        }

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
        printf("mcu update[%s]: %s[%s len %d]\n", __func__, mcu_srec, s_rec, err);
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
//        if (0 != strncmp(rev, s_rec, strlen(s_rec))) {
            printf("mcu update[%s]: version %s <---- %s\n", __func__, rev, s_rec);
//        }

        i = err = 2;
        do {
            if (hex2ch(&rev[i]) < hex2ch(&s_rec[i])) {
                err = 0;
                break;
            }
            i += 2;
        } while ((unsigned int)i < strlen(rev));

        if (err != 0) {
            printf("mcu update[%s]: update is older\n", __func__);
            break;
        }

        // tx start command
        //
        printf("mcu update[%s]: start update [%s]\n", __func__, sta);
        if (0 != tx2mcu(fd_tty, (uint8_t *)sta, strlen(sta))) {
            printf("mcu update[%s]: %s failure to start update cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, strlen(MCU_UPD_OK), MCU_UPD_RX_TO);
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
        printf("mcu update[%s]: erase pflash/nvmflash region [%s]\n", __func__, er);
        if (0 != tx2mcu(fd_tty, (uint8_t *)er, strlen(er))) {
            printf("mcu update[%s]: %s failure to erase cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }
        err = mcu2rx(fd_tty, resp, strlen(MCU_UPD_OK), 4*MCU_UPD_RX_TO);
        if (0 != err) {
            printf("mcu update[%s]: %s mcu don't respond on erase cmd %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        if (0 != strncmp(resp, MCU_UPD_OK, strlen(MCU_UPD_OK))) {
            printf("mcu update[%s]: %s failure to erase %s\n", __func__, tty_n, strerror(errno));
            break;
        }

        printf("mcu update[%s]: send records\n", __func__);
        while (fgets(s_rec, sizeof(s_rec) - 1, fi)) {
            s_rec[sizeof(s_rec) - 1] = 0;

            if ((err = pars_srec(s_rec, strlen(s_rec))) < 0) {
                printf("mcu update[%s]: not s-record %s\n", __func__, s_rec);
            }

            // skip all not relevant instructions
            if (S_REC_8 == err || S_REC_9 == err || S_REC_7 == err) {
                // Temporary don't tx reset instruction
                // tx2mcu(fd_tty, s_rec, strlen(s_rec)); 
            } else if (S_REC_1 == err || S_REC_2 == err || S_REC_3 == err) {
                do {
                    if (0 != tx2mcu(fd_tty, (uint8_t *)s_rec, strlen(s_rec))) {
                        printf("mcu update[%s]: %s failure to tx s-rec %s\n", __func__, tty_n, strerror(errno));
                        break;
                    }
                    memset(resp, 0, strlen(MCU_UPD_nRDY));
                    err = mcu2srec_rx(fd_tty, resp, strlen(MCU_UPD_nRDY), MCU_UPD_RX_TO);
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

        printf("mcu update[%s]: signal about update done\n", __func__);
        if (0 != tx2mcu(fd_tty, (uint8_t *)MCU_UPD_PFD, strlen(MCU_UPD_PFD))) {
            printf("mcu update[%s]: %s failure to transmit finish cmd %s\n", __func__, tty_n, strerror(errno));
        }
    } while (0);

    close(fd_tty);
    if (fi) {
        fclose(fi); 
    }

    printf("Done\n");
#if defined (REDIRECT_STDIO)
    redirect_stdio("/dev/tty");
#endif

    fd_done = open(mcu_update_done, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    close(fd_done);
//    usleep(10000000);

    return EXIT_SUCCESS;
} 
