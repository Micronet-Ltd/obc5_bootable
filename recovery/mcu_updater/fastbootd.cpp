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
//#include "../../system/core/libsparse/include/sparse/sparse.h"


#include "utils.h"
#include "debug.h"

unsigned int debug_level = DEBUG;

struct fastboot_cmd {
    struct fastboot_cmd *next;
    const char *prefix;
    unsigned prefix_len;
    void (* handler)(int src_fd, void *data, int64_t len, const char *arg);
};

static struct fastboot_cmd *cmdlist;

void fastboot_register(const char *prefix, void (* handler)(int src_fd, void *data, int64_t len, const char *arg))
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

enum fb_buffer_type {
    FB_BUFFER,
    FB_BUFFER_SPARSE,
};

struct fastboot_buffer {
    enum fb_buffer_type type;
    void *data;
    unsigned int sz;
};

static void *load_fd(int fd, unsigned *_sz)
{
    char *data;
    int sz;
    int err;

    data = 0;

    sz = get_file_size(fd);
    if (sz < 0) {
        return 0;
    }

    data = (char *)malloc(sz);
    if(!data) {
        return 0;
    }

    err = read(fd, data, sz);

    if(err != sz) {
        free(data);
        return 0;
    }

    if(_sz)
        *_sz = sz;
    return data;
}

#if 0
static struct sparse_file **load_sparse_files(int fd, int max_size)
{
    struct sparse_file *s;
    int files;
    struct sparse_file **out_s;

    s = sparse_file_import_auto(fd, false);
    if (!s) {
        D(ERR,"cannot sparse read file\n");
    }

    files = sparse_file_resparse(s, max_size, NULL, 0);
    if (files < 0) {
        D(ERR,"Failed to resparse\n");
    }

    out_s = (sparse_file **)calloc(sizeof(struct sparse_file *), files + 1);
    if (!out_s) {
        D(ERR,"Failed to allocate sparse file array\n");
    }

    files = sparse_file_resparse(s, max_size, out_s, files);
    if (files < 0) {
        D(ERR,"Failed to resparse\n");
    }

    return out_s;
}
#endif

static void *load_limit_fd(int fd, int64_t *max_size)
{
    char *data;
    int err;

    data = 0;

    data = (char *)malloc(*max_size);
    if(!data) {
        return 0;
    }

    err = read(fd, data, *max_size);

    if(err != *max_size) {
        free(data);
        return 0;
    }

    return data;
}

static int load_buf_fd(int fd, struct fastboot_buffer *buf)
{
    int64_t sz64;
    void *data;
    int64_t limit = 256*1024*1024;

    sz64 = get_file_size(fd);
    if (sz64 < 0) {
        return -1;
    }

    lseek(fd, 0, SEEK_SET);
    if (limit < sz64) {
#if 0
        struct sparse_file **s = load_sparse_files(fd, limit);
        if (s == NULL) {
            return -1;
        }
        buf->type = FB_BUFFER_SPARSE;
        buf->data = s;
#endif
        data = load_limit_fd(fd, &limit);
        if (!data)
            return -1;
        buf->type = FB_BUFFER_SPARSE;
        buf->data = data;
        buf->sz = sz64;
    } else {
        unsigned int sz;
        data = load_fd(fd, &sz);
        if (!data)
            return -1;
        buf->type = FB_BUFFER;
        buf->data = data;
        buf->sz = sz;
    }

    return 0;
}

static void flash_buf(int src_fd, const char *part, fastboot_cmd *fb_cmd, struct fastboot_buffer *buf)
{
    struct sparse_file **s;

    switch (buf->type) {
        case FB_BUFFER_SPARSE:
#if 0
            s = (sparse_file **)buf->data;
            while (*s) {
                int64_t sz64 = sparse_file_len(*s, true, false); // ?
                fb_cmd->handler(src_fd, *s++, sz64, part);
            }
            break;
#endif
        case FB_BUFFER:
            fb_cmd->handler(src_fd, buf->data, buf->sz, part);
            break;
        default:
            D(ERR,"unknown buffer type: %d", buf->type);
    }
}

void fastboot_load_file(int src_fd, const char *part, fastboot_cmd *fb_cmd)
{
    int err;
    struct fastboot_buffer buf;

    err = load_buf_fd(src_fd, &buf);

    if (!err) {
        flash_buf(src_fd, part, fb_cmd, &buf);
        free(buf.data);

        //mount("/dev/block/bootdevice/by-name/system", "/system", "ext4", MS_NOATIME | MS_NODEV | MS_NODIRATIME, 0);

    } else {
        D(INFO,"failure to load dat for %s\n", part);
    }
}

void fastboot_command(char *cmd, char *part, char *arg)
{
    int src_fd;
    struct fastboot_cmd *fb_cmd;

//    D(INFO,"%s %s %s\n", cmd, part, arg);

    for (fb_cmd = cmdlist; fb_cmd; fb_cmd = fb_cmd->next) {
        if (memcmp(cmd, fb_cmd->prefix, fb_cmd->prefix_len)) {
            //D(INFO,"mismatch %s %s", cmd, fb_cmd->prefix);
            continue;
        }

        //D(INFO,"match found %s %s", cmd, fb_cmd->prefix);
        if (arg) {
            src_fd = open(arg, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        } else {
            src_fd = -1;
        }

        if (src_fd < 0) {
            fb_cmd->handler(0, 0, 0, part);
        } else {
            fastboot_load_file(src_fd, part, fb_cmd);
        }

        if (src_fd) {
            close(src_fd);
        }
//        D(INFO,"%s done\n", fb_cmd->prefix);
        return; 
    }
}

extern void commands_init(void);

int fastboot_init(void)
{
    commands_init();

    //parse update rule

    return 0;
}
