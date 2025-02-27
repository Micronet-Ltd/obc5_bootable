/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
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
/*Author:jiao.shp*/

#ifndef _PANEL_COMMON_NT71410_1920_1200_VIDEO_H_
#define _PANEL_COMMON_NT71410_1920_1200_VIDEO_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

#define COMMON_NT71410_1920_1200_SIGNATURE 0x71410
#define	COMMON_NT71410_1920_1200_ID 1
#define COMMON_NT71410_1920_1200_LCD_ADC_STATUS 0
#define	COMMON_NT71410_1920_1200_IC_TYPE 13
#define	COMMON_NT71410_1920_1200_LCD_ADC_MAX  1000000
#define	COMMON_NT71410_1920_1200_LCD_ADC_MIN  0

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config common_nt71410_1920_1200_video_panel_data = {
	"qcom,mdss_dsi_nt71410_1010_wuxga_video", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 0, "DISPLAY_1", 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution common_nt71410_1920_1200_video_panel_res = {
	1200, 1920,70, 80, 3, 0, 20, 21, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel color information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info common_nt71410_1920_1200_video_color = {
	24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel on/off command information                                          */
/*---------------------------------------------------------------------------*/

static char common_nt71410_1920_1200_video_on_cmd60[]={0x11, 0x00, 0x05, 0x80};
static char common_nt71410_1920_1200_video_on_cmd61[]={0x29, 0x00, 0x05, 0x80};

static char common_nt71410_1920_1200_video_on_cmd100[]={0x02,0x00,0x32,0xc0,0x00,0x00,0xff,0xff};

#define PANEL_DELAY 0

static struct mipi_dsi_cmd common_nt71410_1920_1200_video_on_command[] = {
//{sizeof(common_nt71410_1920_1200_video_on_cmd60), (char *)common_nt71410_1920_1200_video_on_cmd60,150},
//{sizeof(common_nt71410_1920_1200_video_on_cmd61), (char *)common_nt71410_1920_1200_video_on_cmd61,50},
	{sizeof(common_nt71410_1920_1200_video_on_cmd100), (char *)common_nt71410_1920_1200_video_on_cmd100,150},	
};

#define COMMON_NT71410_1920_1200_VIDEO_VIDEO_ON_COMMAND ARRAY_SIZE(common_nt71410_1920_1200_video_on_command)


static char common_nt71410_1920_1200_video_off_cmd0[] = {
	0x28, 0x00, 0x05, 0x80
};

static char common_nt71410_1920_1200_video_off_cmd1[] = {
	0x10, 0x00, 0x05, 0x80
};

static char common_nt71410_1920_1200_video_off_cmd100[] = {
	0x02,0x00,0x22,0xc0,0x00,0x00,0xff,0xff
};

static struct mipi_dsi_cmd common_nt71410_1920_1200_video_off_command[] = {
//	{sizeof(common_nt71410_1920_1200_video_off_cmd0), common_nt71410_1920_1200_video_off_cmd0, 0x28},
//	{sizeof(common_nt71410_1920_1200_video_off_cmd1), common_nt71410_1920_1200_video_off_cmd1, 0x78},
{sizeof(common_nt71410_1920_1200_video_off_cmd100), common_nt71410_1920_1200_video_off_cmd100, 0x28},
};

#define COMMON_NT71410_1920_1200_VIDEO_OFF_COMMAND ARRAY_SIZE(common_nt71410_1920_1200_video_off_command)


static struct command_state common_nt71410_1920_1200_video_state = {
	0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info common_nt71410_1920_1200_video_command_panel = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/
static struct videopanel_info common_nt71410_1920_1200_video_video_panel = {
	1, 0, 0, 0, 1, 1, 2, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane configuration                                                        */
/*---------------------------------------------------------------------------*/
static struct lane_configuration common_nt71410_1920_1200_video_lane_config = {
	4, 0, 1, 1, 1, 1
};

/*---------------------------------------------------------------------------*/
/* Panel timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t common_nt71410_1920_1200_video_timings[] = {
	0xf9,0x3d,0x34,0x00,0x58,0x4d,0x36,0x3f,0x53,0x03,0x04,0x00
};

static struct panel_timing common_nt71410_1920_1200_video_timing_info = {
	0, 4, 0x03, 0x12
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence common_nt71410_1920_1200_video_reset_seq = {
	{1, 0, 1, }, {20, 20, 120, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight setting                                                         */
/*---------------------------------------------------------------------------*/
static struct backlight common_nt71410_1920_1200_video_backlight = {
  1, 1, 255, 100, 2, "PMIC_8941"
};
#endif /*_PANEL_COMMON_NT71410_1920_1200_VIDEO_H_*/

