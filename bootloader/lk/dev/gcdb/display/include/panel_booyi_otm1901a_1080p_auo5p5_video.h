/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_BOOYI_OTM1901A_1080P_5P5_VIDEO_H_
#define _PANEL_BOOYI_OTM1901A_1080P_5P5_VIDEO_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

#define BOOYI_OTM1901A_1080P_5P5_VIDEO_SIGNATURE 0x1901
#define BOOYI_OTM1901A_1080P_5P5_VIDEO_ID 1
#define BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_STATUS 1
#define	BOOYI_OTM1901A_1080P_5P5_VIDEO_IC_TYPE 1
#define	BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_MAX  (2000*1000)
#define	BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_MIN  (800*1000)
/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config booyi_otm1901a_1080p_5p5_video_panel_data = {
	"qcom,mdss_dsi_booyi_otm1901_auo5p5_1080p_video", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 0, "DISPLAY_1", 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution booyi_otm1901a_1080p_5p5_video_panel_res = {
	1080, 1920, 36, 28, 4, 0, 13, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel color information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info booyi_otm1901a_1080p_5p5_video_color = {
	24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel on/off command information                                          */
/*---------------------------------------------------------------------------*/
static char  booyi_otm1901a_1080p_5p5_video_on_cmd000[]={0x02,0x00,0x39,0xC0,0x00,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd001[]={0x05,0x00,0x39,0xC0,0xff,0x19,0x01,0x01,0x00,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd002[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd003[]={0x03,0x00,0x39,0xC0,0xff,0x19,0x01,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd004[]={0x02,0x00,0x39,0xC0,0x00,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd005[]={0x02,0x00,0x39,0xC0,0x1c,0x33,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd006[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd007[]={0x02,0x00,0x39,0xC0,0xc1,0xe8,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd008[]={0x02,0x00,0x39,0xC0,0x00,0xa7,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd009[]={0x02,0x00,0x39,0xC0,0xc1,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd010[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd011[]={0x07,0x00,0x39,0xC0,0xc0,0x00,0x2f,0x00,0x00,0x00,0x01,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd012[]={0x02,0x00,0x39,0xC0,0x00,0xc0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd013[]={0x07,0x00,0x39,0xC0,0xc0,0x00,0x2f,0x00,0x00,0x00,0x01,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd014[]={0x02,0x00,0x39,0xC0,0x00,0x9a,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd015[]={0x02,0x00,0x39,0xC0,0xc0,0x1e,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd016[]={0x02,0x00,0x39,0xC0,0x00,0xac,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd017[]={0x02,0x00,0x39,0xC0,0xc0,0x06,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd018[]={0x02,0x00,0x39,0xC0,0x00,0xdc,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd019[]={0x02,0x00,0x39,0xC0,0xc0,0x06,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd020[]={0x02,0x00,0x39,0xC0,0x00,0x81,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd021[]={0x02,0x00,0x39,0xC0,0xa5,0x04,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd022[]={0x02,0x00,0x39,0xC0,0x00,0x92,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd023[]={0x02,0x00,0x39,0xC0,0xe9,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd024[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd025[]={0x02,0x00,0x39,0xC0,0xf3,0x01,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd026[]={0x02,0x00,0x39,0xC0,0x00,0x93,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd027[]={0x02,0x00,0x39,0xC0,0xc5,0x1e,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd028[]={0x02,0x00,0x39,0xC0,0x00,0x95,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd029[]={0x02,0x00,0x39,0xC0,0xc5,0x32,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd030[]={0x02,0x00,0x39,0xC0,0x00,0x97,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd031[]={0x02,0x00,0x39,0xC0,0xc5,0x19,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd032[]={0x02,0x00,0x39,0xC0,0x00,0x99,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd033[]={0x02,0x00,0x39,0xC0,0xc5,0x2d,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd034[]={0x02,0x00,0x39,0xC0,0x00,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd035[]={0x03,0x00,0x39,0xC0,0xd8,0x1f,0x1f,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd036[]={0x02,0x00,0x39,0xC0,0x00,0xb3,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd037[]={0x02,0x00,0x39,0xC0,0xc0,0xcc,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd038[]={0x02,0x00,0x39,0xC0,0x00,0xbc,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd039[]={0x02,0x00,0x39,0xC0,0xc0,0xcc,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd040[]={0x02,0x00,0x39,0xC0,0x00,0xcd,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd041[]={0x02,0x00,0x39,0xC0,0xf5,0x19,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd042[]={0x02,0x00,0x39,0xC0,0x00,0xdb,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd043[]={0x02,0x00,0x39,0xC0,0xf5,0x19,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd044[]={0x02,0x00,0x39,0xC0,0x00,0xf5,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd045[]={0x02,0x00,0x39,0xC0,0xc1,0x40,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd046[]={0x02,0x00,0x39,0xC0,0x00,0xb9,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd047[]={0x02,0x00,0x39,0xC0,0xc0,0x11,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd048[]={0x02,0x00,0x39,0xC0,0x00,0x8d,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd049[]={0x02,0x00,0x39,0xC0,0xf5,0x20,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd050[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd051[]={0x0f,0x00,0x39,0xC0,0xc0,0x00,0x87,0x00,0x04,0x06,0x00,0x87,0x04,0x06,0x00,0x87,0x00,0x04,0x06,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd052[]={0x02,0x00,0x39,0xC0,0x00,0xf0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd053[]={0x07,0x00,0x39,0xC0,0xc3,0x00,0x00,0x00,0x00,0x00,0x80,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd054[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd055[]={0x08,0x00,0x39,0xC0,0xc0,0x00,0x00,0x0c,0x00,0x00,0x1d,0x06};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd056[]={0x02,0x00,0x39,0xC0,0x00,0xd0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd057[]={0x08,0x00,0x39,0xC0,0xc0,0x00,0x00,0x0c,0x00,0x00,0x1d,0x06};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd058[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd059[]={0x05,0x00,0x39,0xC0,0xc2,0x84,0x01,0x45,0x45,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd060[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd061[]={0x0d,0x00,0x39,0xC0,0xc3,0x85,0x03,0x03,0x01,0x00,0x02,0x83,0x04,0x03,0x01,0x00,0x02,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd062[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd063[]={0x0d,0x00,0x39,0xC0,0xc3,0x84,0x04,0x03,0x01,0x00,0x02,0x82,0x04,0x03,0x01,0x00,0x02,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd064[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd065[]={0x10,0x00,0x39,0xC0,0xcc,0x09,0x0a,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x28,0x28,0x28,0x28,0x28};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd066[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd067[]={0x10,0x00,0x39,0xC0,0xcc,0x09,0x0a,0x14,0x13,0x12,0x11,0x18,0x17,0x16,0x15,0x28,0x28,0x28,0x28,0x28};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd068[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd069[]={0x10,0x00,0x39,0xC0,0xcc,0x1d,0x1e,0x1f,0x19,0x1a,0x1b,0x1c,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd070[]={0x02,0x00,0x39,0xC0,0x00,0xb0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd071[]={0x09,0x00,0x39,0xC0,0xcc,0x01,0x02,0x03,0x05,0x06,0x07,0x04,0x08,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd072[]={0x02,0x00,0x39,0xC0,0x00,0xc0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd073[]={0x0d,0x00,0x39,0xC0,0xcc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd074[]={0x02,0x00,0x39,0xC0,0x00,0xd0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd075[]={0x0d,0x00,0x39,0xC0,0xcc,0xc0,0x0c,0x00,0x00,0x05,0xc0,0x00,0x00,0x33,0x03,0x00,0x70,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd076[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd077[]={0x10,0x00,0x39,0xC0,0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd078[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd079[]={0x10,0x00,0x39,0xC0,0xcb,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd080[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd081[]={0x10,0x00,0x39,0xC0,0xcb,0x15,0x00,0x05,0xf5,0x05,0xf5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd082[]={0x02,0x00,0x39,0xC0,0x00,0xb0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd083[]={0x10,0x00,0x39,0xC0,0xcb,0x00,0x01,0xfd,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd084[]={0x02,0x00,0x39,0xC0,0x00,0xc0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd085[]={0x09,0x00,0x39,0xC0,0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd086[]={0x02,0x00,0x39,0xC0,0x00,0xd0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd087[]={0x09,0x00,0x39,0xC0,0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd088[]={0x02,0x00,0x39,0xC0,0x00,0xe0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd089[]={0x09,0x00,0x39,0xC0,0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd090[]={0x02,0x00,0x39,0xC0,0x00,0xf0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd091[]={0x09,0x00,0x39,0xC0,0xcb,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x77,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd092[]={0x02,0x00,0x39,0xC0,0x00,0x80,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd093[]={0x10,0x00,0x39,0xC0,0xcd,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x01,0x12,0x11,0x03,0x04,0x3f,0x17};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd094[]={0x02,0x00,0x39,0xC0,0x00,0x90,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd095[]={0x0c,0x00,0x39,0xC0,0xcd,0x18,0x3f,0x3d,0x25,0x25,0x25,0x1f,0x20,0x21,0x26,0x26};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd096[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd097[]={0x10,0x00,0x39,0xC0,0xcd,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x01,0x12,0x11,0x05,0x06,0x3f,0x17};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd098[]={0x02,0x00,0x39,0xC0,0x00,0xb0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd099[]={0x0c,0x00,0x39,0xC0,0xcd,0x18,0x3f,0x3d,0x25,0x25,0x25,0x1f,0x20,0x21,0x26,0x26};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd100[]={0x02,0x00,0x39,0xC0,0x00,0xc2,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd101[]={0x02,0x00,0x39,0xC0,0xc5,0x12,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd102[]={0x02,0x00,0x39,0xC0,0x00,0xa8,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd103[]={0x02,0x00,0x39,0xC0,0xc4,0x12,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd104[]={0x02,0x00,0x39,0xC0,0x00,0xa0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd105[]={0x05,0x00,0x39,0xC0,0xc4,0x30,0x26,0x04,0x3a,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd106[]={0x02,0x00,0x39,0xC0,0x00,0xa4,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd107[]={0x05,0x00,0x39,0xC0,0xc4,0x30,0x26,0x84,0x3a,0xFF,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd108[]={0x02,0x00,0x39,0xC0,0x00,0xe1,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd109[]={0x02,0x00,0x39,0xC0,0xf5,0x45,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd110[]={0x02,0x00,0x39,0xC0,0x00,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd111[]={0x04,0x00,0x39,0xC0,0xff,0xff,0xff,0xff};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd112[]={0x02,0x00,0x39,0xC0,0x11,0x00,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmd113[]={0x02,0x00,0x39,0xC0,0x29,0x00,0xFF,0xFF};

static char booyi_otm1901a_1080p_5p5_video_on_cmd114[]={0x02,0x00,0x29,0xC0,0x00,0x00,0xff,0xff};      
static char booyi_otm1901a_1080p_5p5_video_on_cmd115[]={0x02,0x00,0x29,0xC0,0x51,0xff,0xff,0xff};  
static char booyi_otm1901a_1080p_5p5_video_on_cmd116[]={0x02,0x00,0x29,0xC0,0x00,0x00,0xff,0xff}; 
static char booyi_otm1901a_1080p_5p5_video_on_cmd117[]={0x02,0x00,0x29,0xC0,0x53,0x24,0xff,0xff}; 
static char booyi_otm1901a_1080p_5p5_video_on_cmd118[]={0x02,0x00,0x29,0xC0,0x00,0x00,0xff,0xff}; 
static char booyi_otm1901a_1080p_5p5_video_on_cmd119[]={0x02,0x00,0x29,0xC0,0x55,0x01,0xff,0xff};  


static char  booyi_otm1901a_1080p_5p5_video_on_cmdAdd100[]={0x02,0x00,0x39,0xC0,0x00,0xB0,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmdAdd101[]={0x02,0x00,0x39,0xC0,0xCA,0x01,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmdAdd102[]={0x02,0x00,0x39,0xC0,0x00,0xB3,0xFF,0xFF};
static char  booyi_otm1901a_1080p_5p5_video_on_cmdAdd103[]={0x02,0x00,0x39,0xC0,0xCA,0x40,0xFF,0xFF};


static struct mipi_dsi_cmd booyi_otm1901a_1080p_5p5_video_on_command[] = {
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd000),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd000, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd001),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd001, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd002),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd002, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd003),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd003, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd004),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd004, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd005),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd005, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd006),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd006, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd007),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd007, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd008),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd008, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd009),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd009, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd010),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd010, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd011),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd011, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd012),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd012, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd013),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd013, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd014),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd014, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd015),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd015, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd016),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd016, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd017),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd017, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd018),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd018, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd019),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd019, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd020),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd020, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd021),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd021, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd022),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd022, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd023),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd023, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd024),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd024, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd025),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd025, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd026),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd026, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd027),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd027, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd028),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd028, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd029),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd029, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd030),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd030, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd031),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd031, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd032),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd032, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd033),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd033, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd034),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd034, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd035),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd035, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd036),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd036, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd037),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd037, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd038),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd038, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd039),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd039, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd040),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd040, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd041),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd041, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd042),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd042, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd043),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd043, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd044),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd044, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd045),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd045, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd046),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd046, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd047),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd047, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd048),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd048, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd049),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd049, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd050),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd050, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd051),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd051, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd052),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd052, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd053),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd053, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd054),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd054, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd055),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd055, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd056),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd056, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd057),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd057, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd058),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd058, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd059),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd059, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd060),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd060, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd061),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd061, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd062),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd062, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd063),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd063, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd064),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd064, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd065),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd065, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd066),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd066, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd067),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd067, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd068),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd068, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd069),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd069, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd070),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd070, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd071),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd071, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd072),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd072, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd073),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd073, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd074),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd074, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd075),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd075, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd076),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd076, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd077),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd077, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd078),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd078, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd079),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd079, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd080),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd080, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd081),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd081, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd082),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd082, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd083),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd083, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd084),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd084, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd085),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd085, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd086),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd086, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd087),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd087, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd088),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd088, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd089),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd089, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd090),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd090, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd091),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd091, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd092),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd092, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd093),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd093, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd094),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd094, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd095),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd095, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd096),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd096, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd097),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd097, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd098),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd098, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd099),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd099, 0x00},
	
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmdAdd100),(char *)booyi_otm1901a_1080p_5p5_video_on_cmdAdd100, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmdAdd101),(char *)booyi_otm1901a_1080p_5p5_video_on_cmdAdd101, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmdAdd102),(char *)booyi_otm1901a_1080p_5p5_video_on_cmdAdd102, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmdAdd103),(char *)booyi_otm1901a_1080p_5p5_video_on_cmdAdd103, 0x00},
	
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd100),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd100, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd101),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd101, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd102),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd102, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd103),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd103, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd104),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd104, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd105),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd105, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd106),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd106, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd107),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd107, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd108),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd108, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd109),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd109, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd110),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd110, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd111),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd111, 0x00},	
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd114),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd114, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd115),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd115, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd116),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd116, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd117),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd117, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd118),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd118, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd119),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd119, 0x00},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd112),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd112, 0xC8},
	{sizeof(booyi_otm1901a_1080p_5p5_video_on_cmd113),(char *)booyi_otm1901a_1080p_5p5_video_on_cmd113, 0x78},
};

#define BOOYI_OTM1901A_1080P_5P5_VIDEO_ON_COMMAND ARRAY_SIZE(booyi_otm1901a_1080p_5p5_video_on_command)


static char booyi_otm1901a_1080p_5p5_videooff_cmd0[] = {
	0x28, 0x00, 0x05, 0x80
};

static char booyi_otm1901a_1080p_5p5_videooff_cmd1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd booyi_otm1901a_1080p_5p5_video_off_command[] = {
	{0x4, booyi_otm1901a_1080p_5p5_videooff_cmd0, 0x32},
	{0x4, booyi_otm1901a_1080p_5p5_videooff_cmd1, 0x78}
};

#define BOOYI_OTM1901A_1080P_5P5_VIDEO_OFF_COMMAND 2


static struct command_state booyi_otm1901a_1080p_5p5_video_state = {
	0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info booyi_otm1901a_1080p_5p5_video_command_panel = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/
static struct videopanel_info booyi_otm1901a_1080p_5p5_video_video_panel = {
	1, 0, 0, 0, 1, 1, 2, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane configuration                                                        */
/*---------------------------------------------------------------------------*/
static struct lane_configuration booyi_otm1901a_1080p_5p5_video_lane_config = {
	4, 0, 1, 1, 1, 1
};

/*---------------------------------------------------------------------------*/
/* Panel timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t booyi_otm1901a_1080p_5p5_video_timings[] = {
	//0x9e, 0x43, 0x37, 0x00, 0x60, 0x58, 0x39, 0x45, 0x5b, 0x03, 0x04, 0x00
	  0xf9,0x3d,0x34,0x00,0x58,0x4d,0x36,0x3f,0x53,0x03,0x04,0x00
};

static struct panel_timing booyi_otm1901a_1080p_5p5_video_timing_info = {
	0, 4, 0x1e, 0x38
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence booyi_otm1901a_1080p_5p5_video_panel_reset_seq = {
	{1, 0, 1, }, {50, 50, 150, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight setting                                                         */
/*---------------------------------------------------------------------------*/
static struct backlight booyi_otm1901a_1080p_5p5_video_backlight = {
  2, 0, 255, 0, 1, 0
//	  1, 1, 255, 100, 2, "PMIC_8941"
};
#endif /*_PANEL_BOOYI_OTM1901A_1080P_5P5_VIDEO_H_*/
