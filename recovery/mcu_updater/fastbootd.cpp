/*
 * Copyright (C) 2016 Micronet Inc
 * <vladimir.zatulovsky@micronet-inc.com>
 * 
 * Copyright (C) 2013 The Android Open Source Project
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

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cutils/klog.h>


#include "debug.h"

unsigned int debug_level = DEBUG;

struct fastboot_cmd {
    struct fastboot_cmd *next;
    const char *prefix;
    unsigned prefix_len;
    void (* handler)(int src_fd, const char *arg);
};

static struct fastboot_cmd *cmdlist;

void fastboot_register(const char *prefix, void (* handler)(int src_fd, const char *arg))
{
    struct fastboot_cmd *cmd;
    cmd = (struct fastboot_cmd *)malloc(sizeof(*cmd));
    if (cmd) {
        cmd->prefix = prefix;
        cmd->prefix_len = strlen(prefix);
        cmd->handler = handler;
        cmd->next = cmdlist;
        cmdlist = cmd;
    }
}

void fastboot_command(char *cmd, char *part, char *arg)
{
    int src_fd;
    struct fastboot_cmd *fb_cmd;

    D(INFO,"%s %s %s\n", cmd, part, arg);


    for (fb_cmd = cmdlist; fb_cmd; fb_cmd = fb_cmd->next) {
        if (memcmp(cmd, fb_cmd->prefix, fb_cmd->prefix_len)) {
            D(INFO,"mismatch %s %s", cmd, fb_cmd->prefix);
            continue;
        }

        D(INFO,"match found %s %s", cmd, fb_cmd->prefix);
        if (arg) {
            src_fd = open(arg, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
        } else {
            src_fd = 0;
        }

        fb_cmd->handler(src_fd, part);

        if (src_fd) {
            close(src_fd);
        }
        D(INFO,"%s done\n", fb_cmd->prefix);
        return; 
    }
}
#if 0
static int load_buf_fd(int fd, struct fastboot_buffer *buf)
{
    int64_t sz64;
    void *data;
    int64_t limit;

    sz64 = get_file_size(fd);
    if (sz64 < 0) {
        return -1;
    }

    lseek(fd, 0, SEEK_SET);
    limit = get_sparse_limit(usb, sz64);
    if (limit) {
        struct sparse_file **s = load_sparse_files(fd, limit);
        if (s == NULL) {
            return -1;
        }
        buf->type = FB_BUFFER_SPARSE;
        buf->data = s;
    } else {
        unsigned int sz;
        data = load_fd(fd, &sz);
        if (data == 0) return -1;
        buf->type = FB_BUFFER;
        buf->data = data;
        buf->sz = sz;
    }

    return 0;
}

void fastboot_load_file(int src_fd, const char *part, fastboot_cmd *fb_cmd)
{
    struct fastboot_buffer buf;

    if (load_buf(usb, fname, &buf)) {
        die("cannot load '%s'", fname);
    }
    flash_buf(pname, &buf);
}
#endif

extern void commands_init(void);

int fastboot_init(void)
{
    commands_init();

    //parse update rule

    return 0;
}
