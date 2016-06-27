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
#include <cutils/klog.h>
#include <getopt.h>
#include <stdlib.h>


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

extern void commands_init(void);

int fastboot_init(void)
{
    commands_init();

    //parse update rule

    return 0;
}
