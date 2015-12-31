/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
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
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_TRULY_WVGA_CMD_H_
#define _PANEL_TRULY_WVGA_CMD_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config truly_wvga_cmd_panel_data = {
	"qcom,mdss_dsi_truly_wvga_cmd", "dsi:0:", "qcom,mdss-dsi-panel",
	11, 1, "DISPLAY_1", 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution truly_wvga_cmd_panel_res = {
	480, 800, 160, 40, 8, 0, 12, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel color information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info truly_wvga_cmd_color = {
	24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel on/off command information                                          */
/*---------------------------------------------------------------------------*/
static char truly_wvga_cmd_on_cmd0[] = {
	0x01, 0x00, 0x05, 0x80
};

static char truly_wvga_cmd_on_cmd1[] = {
	0xb0, 0x04, 0x23, 0x80
};

static char truly_wvga_cmd_on_cmd2[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xb3, 0x02, 0x00, 0xFF,
};

static char truly_wvga_cmd_on_cmd3[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xb6, 0x51, 0x83, 0xFF,
};

static char truly_wvga_cmd_on_cmd4[] = {
	0x05, 0x00, 0x29, 0xC0,
	0xb7, 0x00, 0x80, 0x15,
	0x25, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd5[] = {
	0x14, 0x00, 0x29, 0xC0,
	0xb8, 0x00, 0x07, 0x07,
	0xff, 0xc8, 0xc8, 0x01,
	0x18, 0x10, 0x10, 0x37,
	0x5a, 0x87, 0xde, 0xff,
	0x00, 0x00, 0x00, 0x00,
};

static char truly_wvga_cmd_on_cmd6[] = {
	0x05, 0x00, 0x29, 0xC0,
	0xb9, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd7[] = {
	0xbd, 0x00, 0x23, 0x80
};

static char truly_wvga_cmd_on_cmd8[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xc0, 0x02, 0x43, 0xFF,
};

static char truly_wvga_cmd_on_cmd9[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xc1, 0x43, 0x31, 0x99,
	0x21, 0x20, 0x00, 0x10,
	0x28, 0x0c, 0x0c, 0x00,
	0x00, 0x00, 0x21, 0x01,
};

static char truly_wvga_cmd_on_cmd10[] = {
	0x07, 0x00, 0x29, 0xC0,
	0xc2, 0x28, 0x06, 0x06,
	0x01, 0x03, 0x00, 0xFF,
};

static char truly_wvga_cmd_on_cmd11[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xc3, 0x40, 0x00, 0x03,
};

static char truly_wvga_cmd_on_cmd12[] = {
	0x03, 0x00, 0x29, 0xC0,
	0x6f, 0x03, 0x00, 0xFF,
};

static char truly_wvga_cmd_on_cmd13[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xc4, 0x00, 0x01, 0xFF,
};

static char truly_wvga_cmd_on_cmd14[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xc6, 0x00, 0x00, 0xFF,
};

static char truly_wvga_cmd_on_cmd15[] = {
	0x06, 0x00, 0x29, 0xC0,
	0xc7, 0x11, 0x8d, 0xa0,
	0xf5, 0x27, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd16[] = {
	0x19, 0x00, 0x29, 0xC0,
	0xc8, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd17[] = {
	0x19, 0x00, 0x29, 0xC0,
	0xc9, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd18[] = {
	0x19, 0x00, 0x29, 0xC0,
	0xca, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0x01, 0x0a, 0x12,
	0x1c, 0x2b, 0x45, 0x3f,
	0x29, 0x17, 0x13, 0x0f,
	0x04, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd19[] = {
	0x11, 0x00, 0x29, 0xC0,
	0xd0, 0x99, 0x03, 0xce,
	0xa6, 0x00, 0x43, 0x20,
	0x10, 0x01, 0x00, 0x01,
	0x01, 0x00, 0x03, 0x01,
	0x00, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd20[] = {
	0x08, 0x00, 0x29, 0xC0,
	0xd1, 0x18, 0x0C, 0x23,
	0x03, 0x75, 0x02, 0x50,
};

static char truly_wvga_cmd_on_cmd21[] = {
	0xd3, 0x33, 0x23, 0x80
};

static char truly_wvga_cmd_on_cmd22[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xd5, 0x2a, 0x2a, 0xFF,
};

static char truly_wvga_cmd_on_cmd23[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xd6, 0x28, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd24[] = {
	0x10, 0x00, 0x29, 0xC0,
	0xd7, 0x01, 0x00, 0xaa,
	0xc0, 0x2a, 0x2c, 0x22,
	0x12, 0x71, 0x0a, 0x12,
	0x00, 0xa0, 0x00, 0x03,
};

static char truly_wvga_cmd_on_cmd25[] = {
	0x09, 0x00, 0x29, 0xC0,
	0xd8, 0x44, 0x44, 0x22,
	0x44, 0x21, 0x46, 0x42,
	0x40, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd26[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xd9, 0xcf, 0x2d, 0x51,
};

static char truly_wvga_cmd_on_cmd27[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xda, 0x01, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd28[] = {
	0x03, 0x00, 0x29, 0xC0,
	0xde, 0x01, 0x4f, 0xFF,
};

static char truly_wvga_cmd_on_cmd29[] = {
	0x07, 0x00, 0x29, 0xC0,
	0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
};

static char truly_wvga_cmd_on_cmd30[] = {
	0xe6, 0x4f, 0x23, 0x80
};

static char truly_wvga_cmd_on_cmd31[] = {
	0x06, 0x00, 0x29, 0xC0,
	0xf3, 0x06, 0x00, 0x00,
	0x24, 0x00, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd32[] = {
	0x02, 0x00, 0x29, 0xC0,
	0xf8, 0x00, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd33[] = {
	0xfa, 0x03, 0x23, 0x80
};

static char truly_wvga_cmd_on_cmd34[] = {
	0x04, 0x00, 0x29, 0xC0,
	0xfb, 0x00, 0x00, 0x00,
};

static char truly_wvga_cmd_on_cmd35[] = {
	0x06, 0x00, 0x29, 0xC0,
	0xfc, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd36[] = {
	0x05, 0x00, 0x29, 0xC0,
	0xfd, 0x00, 0x00, 0x70,
	0x00, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd37[] = {
	0x05, 0x00, 0x39, 0xC0,
	0x2a, 0x00, 0x00, 0x01,
	0xdf, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd38[] = {
	0x05, 0x00, 0x39, 0xC0,
	0x2b, 0x00, 0x00, 0x03,
	0x1f, 0xFF, 0xFF, 0xFF,
};

static char truly_wvga_cmd_on_cmd39[] = {
	0x35, 0x00, 0x15, 0x80
};

static char truly_wvga_cmd_on_cmd40[] = {
	0x03, 0x00, 0x39, 0xC0,
	0x44, 0x00, 0x50, 0xFF,
};

static char truly_wvga_cmd_on_cmd41[] = {
	0x36, 0x41, 0x15, 0x80
};

static char truly_wvga_cmd_on_cmd42[] = {
	0x3a, 0x77, 0x15, 0x80
};

static char truly_wvga_cmd_on_cmd43[] = {
	0x11, 0x00, 0x05, 0x80
};

static char truly_wvga_cmd_on_cmd44[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd truly_wvga_cmd_on_command[] = {
	{0x4, truly_wvga_cmd_on_cmd0, 0x00},
	{0x4, truly_wvga_cmd_on_cmd1, 0x00},
	{0x8, truly_wvga_cmd_on_cmd2, 0x00},
	{0x8, truly_wvga_cmd_on_cmd3, 0x00},
	{0xc, truly_wvga_cmd_on_cmd4, 0x00},
	{0x18, truly_wvga_cmd_on_cmd5, 0x00},
	{0xc, truly_wvga_cmd_on_cmd6, 0x00},
	{0x4, truly_wvga_cmd_on_cmd7, 0x00},
	{0x8, truly_wvga_cmd_on_cmd8, 0x00},
	{0x14, truly_wvga_cmd_on_cmd9, 0x00},
	{0xc, truly_wvga_cmd_on_cmd10, 0x00},
	{0x8, truly_wvga_cmd_on_cmd11, 0x00},
	{0x8, truly_wvga_cmd_on_cmd12, 0x00},
	{0x8, truly_wvga_cmd_on_cmd13, 0x00},
	{0x8, truly_wvga_cmd_on_cmd14, 0x00},
	{0xc, truly_wvga_cmd_on_cmd15, 0x00},
	{0x20, truly_wvga_cmd_on_cmd16, 0x00},
	{0x20, truly_wvga_cmd_on_cmd17, 0x00},
	{0x20, truly_wvga_cmd_on_cmd18, 0x00},
	{0x18, truly_wvga_cmd_on_cmd19, 0x00},
	{0xc, truly_wvga_cmd_on_cmd20, 0x00},
	{0x4, truly_wvga_cmd_on_cmd21, 0x00},
	{0x8, truly_wvga_cmd_on_cmd22, 0x00},
	{0x8, truly_wvga_cmd_on_cmd23, 0x00},
	{0x14, truly_wvga_cmd_on_cmd24, 0x00},
	{0x10, truly_wvga_cmd_on_cmd25, 0x00},
	{0x8, truly_wvga_cmd_on_cmd26, 0x00},
	{0x8, truly_wvga_cmd_on_cmd27, 0x00},
	{0x8, truly_wvga_cmd_on_cmd28, 0x00},
	{0xc, truly_wvga_cmd_on_cmd29, 0x00},
	{0x4, truly_wvga_cmd_on_cmd30, 0x00},
	{0xc, truly_wvga_cmd_on_cmd31, 0x00},
	{0x8, truly_wvga_cmd_on_cmd32, 0x00},
	{0x4, truly_wvga_cmd_on_cmd33, 0x00},
	{0x8, truly_wvga_cmd_on_cmd34, 0x00},
	{0xc, truly_wvga_cmd_on_cmd35, 0x00},
	{0xc, truly_wvga_cmd_on_cmd36, 0x00},
	{0xc, truly_wvga_cmd_on_cmd37, 0x00},
	{0xc, truly_wvga_cmd_on_cmd38, 0x00},
	{0x4, truly_wvga_cmd_on_cmd39, 0x00},
	{0x8, truly_wvga_cmd_on_cmd40, 0x00},
	{0x4, truly_wvga_cmd_on_cmd41, 0x00},
	{0x4, truly_wvga_cmd_on_cmd42, 0x00},
	{0x4, truly_wvga_cmd_on_cmd43, 0x7D},
	{0x4, truly_wvga_cmd_on_cmd44, 0x3c}
};

#define TRULY_WVGA_CMD_ON_COMMAND 45


static char truly_wvga_cmdoff_cmd0[] = {
	0x28, 0x00, 0x05, 0x80
};

static char truly_wvga_cmdoff_cmd1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd truly_wvga_cmd_off_command[] = {
	{0x4, truly_wvga_cmdoff_cmd0, 0x32},
	{0x4, truly_wvga_cmdoff_cmd1, 0x78}
};

#define TRULY_WVGA_CMD_OFF_COMMAND 2


static struct command_state truly_wvga_cmd_state = {
	0, 0
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info truly_wvga_cmd_command_panel = {
	1, 1, 1, 0, 0, 0x2c, 0, 0, 0, 1, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/
static struct videopanel_info truly_wvga_cmd_video_panel = {
	0, 0, 0, 0, 1, 1, 1, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane configuration                                                        */
/*---------------------------------------------------------------------------*/
static struct lane_configuration truly_wvga_cmd_lane_config = {
	2, 0, 1, 1, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t truly_wvga_cmd_timings[] = {
	0x7B, 0x1A, 0x10, 0x00, 0x3C, 0x42, 0x14, 0x1C, 0x15, 0x3, 0x4, 0x00
};

static struct panel_timing truly_wvga_cmd_timing_info = {
	2, 4, 0x04, 0x1a
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence truly_wvga_cmd_reset_seq = {
	{2, 0, 2, }, {20, 2, 20, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight setting                                                         */
/*---------------------------------------------------------------------------*/
static struct backlight truly_wvga_cmd_backlight = {
	0, 1, 255, 0, 1, 0
};

#endif /*_PANEL_TRULY_WVGA_CMD_H_*/
