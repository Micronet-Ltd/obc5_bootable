/*
 * Copyright (C) 2016 Micronet Inc
 * <vladimir.zatulovsky@micronet-inc.com>
 * 
 * Copyright (c) 2009-2013, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Google, Inc. nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <sys/reboot.h>
//#include <sys/ioctl.h>
#include <sys/mount.h>

#include "bootimg.h"
//#include "commands/boot.h"
#include "flash.h"
#include "partitions.h"
#include "virtual_partitions.h"
#include "debug.h"
//#include "protocol.h"
//#include "trigger.h"
#include "utils.h"
//#include <cutils/config_utils.h>


#define BUFFER_SIZE 1024 * 1024
#define MIN(a, b) (a > b ? b : a)

static int GPT_header_location (void) {
    printf("%s: using second sector\n", __func__);
    return 1;
}

int trigger_gpt_layout(struct GPT_content *table) {
    printf("%s: %p", __func__, table);
    return 0;
}

void cmd_gpt_layout (int src_fd, const char *blk_dev, const char *arg) {
    struct GPT_entry_table *old_table;
    struct GPT_content entry;

    if (!blk_dev || !strcmp(blk_dev, "")) {
        printf("%s: blockdev not defined in config file\n", __func__);
        return;
    }

    //TODO: add same verification as in cmd_flash
    if (src_fd < 0) {
        printf("%s: no layout file\n", __func__);
        return;
    }

    old_table = GPT_get_device(blk_dev, GPT_header_location());

    GPT_default_content(&entry, old_table);
    if (!old_table)
        printf("%s: Could not get old gpt table\n", __func__);
    else
        GPT_release_device(old_table);

    if (!GPT_parse_file(src_fd, &entry)) {
        printf("%s: Could not parse partition config file\n", __func__);
        return;
    }

    if (trigger_gpt_layout(&entry)) {
        printf("%s: Vendor forbids this opperation\n", __func__);
        GPT_release_content(&entry);
        return;
    }

    if (!GPT_write_content(blk_dev, &entry)) {
        printf("%s: Unable to write gpt file\n", __func__);
        GPT_release_content(&entry);
        return;
    }

    GPT_release_content(&entry);
    printf("%s: done\n", __func__);
}

struct block_device {
    const char *part_name;
    const char *blk_dev_name;
};

struct block_device avail_block_devices[] = {
    {"/system", "/dev/block/bootdevice/by-name/system"},
    {"/cache", "/dev/block/bootdevice/by-name/cache"},
    {"/data", "/dev/block/bootdevice/by-name/userdata"},
    {"/boot", "/dev/block/bootdevice/by-name/boot"},
    {"/recovery", "/dev/block/bootdevice/by-name/recovery"},
    {"/misc", "/dev/block/bootdevice/by-name/misc"},
};

#define BLK_DEV_PREF "/dev/block/bootdevice/by-name"

int flash_find_entry(const char *blk_dev_name, char *out, size_t out_len)
{
    if (strlen(BLK_DEV_PREF) + strlen(blk_dev_name) + 1 > out_len) {
        D(ERR, "not enough memory %s:%s [%d]", BLK_DEV_PREF, blk_dev_name, (int)out_len);
        return -1;
    }

    snprintf(out, out_len, "%s%s", BLK_DEV_PREF, blk_dev_name);

    if (access(out, F_OK ) == -1) {
        D(ERR, "could not find partition file %s", blk_dev_name);
        return -1;
    }

    return 0;
}

int flash_erase(int fd)
{
    int64_t size;
    size = get_block_device_size(fd);
    D(DEBUG, "erase %"PRId64" data from %d\n", size, fd);

    return wipe_block_device(fd, size);
}

int flash_write(int partition_fd, int data_fd, ssize_t size, ssize_t skip)
{
    ssize_t written = 0;
    struct GPT_mapping input;
    struct GPT_mapping output;

    while (written < size) {
        int current_size = MIN(size - written, BUFFER_SIZE);

        if (gpt_mmap(&input, written + skip, current_size, data_fd)) {
            D(ERR, "Error in writing data, unable to map data file %zd at %zd size %d", size, skip, current_size);
            return -1;
        }
        if (gpt_mmap(&output, written, current_size, partition_fd)) {
            D(ERR, "Error in writing data, unable to map output partition");
            return -1;
        }

        memcpy(output.ptr, input.ptr, current_size);

        gpt_unmap(&input);
        gpt_unmap(&output);

        written += current_size;
    }

    return 0;
}

static void cmd_erase(int src_fd, const char *arg)
{
    int partition_fd;
    char path[PATH_MAX];

    printf("%s: %s\n", __func__, arg);

    if (flash_find_entry(arg, path, PATH_MAX)) {
        printf("%s: Couldn't find partition\n", __func__);
        printf("%s: partition table doesn't exist\n", __func__);
        return;
    }

    printf("%s: unmount %s\n", __func__, arg);
    if (!(0 == umount(arg) || errno == EINVAL || errno == ENOENT)) {
        printf("%s: failure unmount %s[%s]\n", __func__, arg, strerror(errno));
        return;
    }

    partition_fd = flash_get_partiton(path);
    if (partition_fd < 0) {
        printf("%s: partiton file does not exists\n", __func__);
    }

    if (flash_erase(partition_fd)) {
        printf("%s: failed to erase partition\n", __func__);
        flash_close(partition_fd);
        return;
    }

    if (flash_close(partition_fd) < 0) {
        printf("%s: could not close device %s\n", __func__, strerror(errno));
        printf("%s: failed to erase partition\n", __func__);
        return;
    }
    printf("%s: Done\n", __func__);
}

static void cmd_flash(int src_fd, const char *arg)
{
    int partition;
    uint64_t sz;
    char data[BOOT_MAGIC_SIZE];
    char path[PATH_MAX];
    ssize_t header_sz = 0;
    int data_fd = 0;

    printf("%s: cmd_flash %s\n", __func__, arg);

#if 0
    if (try_handle_virtual_partition(phandle, arg)) {
        return;
    }

    if (phandle->download_fd < 0) {
        fastboot_fail(phandle, "no kernel file");
        return;
    }

    if (flash_find_entry(arg, path, PATH_MAX)) {
        fastboot_fail(phandle, "partition table doesn't exist");
        return;
    }

    if (flash_validate_certificate(phandle->download_fd, &data_fd) != 1) {
        fastboot_fail(phandle, "Access forbiden you need certificate");
        return;
    }

    // TODO: Maybe its goot idea to check whether the partition is bootable
    if (!strcmp(arg, "boot") || !strcmp(arg, "recovery")) {
        if (read_data_once(data_fd, data, BOOT_MAGIC_SIZE) < BOOT_MAGIC_SIZE) {
            fastboot_fail(phandle, "incoming data read error, cannot read boot header");
            return;
        }
        if (memcmp((void *)data, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
            fastboot_fail(phandle, "image is not a boot image");
            return;
        }
    }

    partition = flash_get_partiton(path);

    sz = get_file_size64(data_fd);

    sz -= header_sz;

    if (sz > get_file_size64(partition)) {
        flash_close(partition);
        printf("%s: size of file too large\n", __func__);
        fastboot_fail(phandle, "size of file too large");
        return;
    }

    printf("%s: writing %"PRId64" bytes to '%s'\n", __func__, sz, arg);

    if (flash_write(partition, phandle->download_fd, sz, header_sz)) {
        fastboot_fail(phandle, "flash write failure");
        return;
    }
    printf("s: partition '%s' updated\n", __func__, arg);

    flash_close(partition);
    close(data_fd);

    fastboot_okay(phandle, "");
#endif
}

extern void fastboot_register(const char *prefix, void (* handler)(int src_fd, const char *arg));

void commands_init(void)
{
    virtual_partition_register("partition-table", cmd_gpt_layout);

    fastboot_register("erase:", cmd_erase);
    fastboot_register("flash:", cmd_flash);
}

