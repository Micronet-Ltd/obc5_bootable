/* Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
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

#include <debug.h>
#include <err.h>
#include <smem.h>
#include <msm_panel.h>
#include <board.h>
#include <mipi_dsi.h>
#include <target/display.h>

#include "include/panel.h"
#include "panel_display.h"

/*---------------------------------------------------------------------------*/
/* GCDB Panel Database                                                       */
/*---------------------------------------------------------------------------*/
#include "panel_samsung_s6d7aa0x01_1280_800_video.h"
#include "panel_boe_ili6366s_wxga_video.h"

#include "panel_booyi_otm1901a_1080p_auo5p5_video.h"
#include "panel_gongtai_otm1901a_1080p_auo5p5_video.h"
#include "panel_txd_nt35596_1080p_video.h"

#include "panel_h8394d-txd-innolux5p5-hd-video.h"
#include "panel_h8394f-jd-auo5p5-hd-video.h"
#include "panel_otm1284_lead_hd_cpt_550_video.h"
#include "panel_nt71410_1920_1200_1010_video.h"
#include "panel_bp080wx1_s6d7aa0x01_1280_800_video.h"
#include "panel_nt35521s_720p_video.h"
#include "panel_st7703-hxgd-hd-5p5-video.h"

#define DISPLAY_MAX_PANEL_DETECTION 6
#define OTM8019A_FWVGA_VIDEO_PANEL_ON_DELAY 50
#define NT35590_720P_CMD_PANEL_ON_DELAY 40

/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
static uint32_t auto_pan_loop = 0;

/*
 * The list of panels that are supported on this target.
 * Any panel in this list can be selected using fastboot oem command.
 */
static struct panel_list supp_panels[] = {
	{"jdi_1080p_video", JDI_1080P_VIDEO_PANEL},
	{"nt35590_720p_video", NT35590_720P_VIDEO_PANEL},
	{"nt35590_720p_cmd", NT35590_720P_CMD_PANEL},
	{"innolux_720p_video", INNOLUX_720P_VIDEO_PANEL},
	{"otm8019a_fwvga_video", OTM8019A_FWVGA_VIDEO_PANEL},
	{"otm1283a_720p_video", OTM1283A_720P_VIDEO_PANEL},
	{"nt35596_1080p_video", NT35596_1080P_VIDEO_PANEL},
	{"sharp_wqxga_dualdsi_video",SHARP_WQXGA_DUALDSI_VIDEO_PANEL},
	{"jdi_fhd_video", JDI_FHD_VIDEO_PANEL},
	{"hx8379a_wvga_video", HX8379A_FWVGA_VIDEO_PANEL},
	{"hx8394d_720p_video", HX8394D_720P_VIDEO_PANEL},
	{"nt35521_wxga_video", NT35521_WXGA_VIDEO_PANEL},
	{"r61318_hd_video", R61318_HD_VIDEO_PANEL},
	{"r63417_1080p_video", R63417_1080P_VIDEO_PANEL},
	{"jdi_a216_fhd_video", JDI_A216_FHD_VIDEO_PANEL},
};

static uint32_t panel_id;

int oem_panel_rotation()
{
	return NO_ERROR;
}

int oem_panel_on()
{
	/*
	 *OEM can keep their panel specific on instructions in this
	 *function
	 */
	if (panel_id == OTM8019A_FWVGA_VIDEO_PANEL) {
		/* needs extra delay to avoid unexpected artifacts */
		mdelay(OTM8019A_FWVGA_VIDEO_PANEL_ON_DELAY);
	} else if (panel_id == NT35590_720P_CMD_PANEL) {
		/* needs extra delay to avoid snow screen artifacts */
		mdelay(NT35590_720P_CMD_PANEL_ON_DELAY);
	}

	return NO_ERROR;
}

int oem_panel_off()
{
	/* OEM can keep their panel specific off instructions
	 * in this function
	 */
	return NO_ERROR;
}

static int init_panel_data(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	int pan_type = PANEL_TYPE_DSI;

	switch (panel_id) {
    case SAMSUNG_S6D7AA0X01_1280_800_VIDEO_PANEL:
		panelstruct->paneldata    = &samsung_s6d7aa0x01_1280_800_video_panel_data;
		panelstruct->panelres     = &samsung_s6d7aa0x01_1280_800_video_panel_res;
		panelstruct->color        = &samsung_s6d7aa0x01_1280_800_video_color;
		panelstruct->videopanel   = &samsung_s6d7aa0x01_1280_800_video_video_panel;
		panelstruct->commandpanel = &samsung_s6d7aa0x01_1280_800_video_command_panel;
		panelstruct->state        = &samsung_s6d7aa0x01_1280_800_video_state;
		panelstruct->laneconfig   = &samsung_s6d7aa0x01_1280_800_video_lane_config;
		panelstruct->paneltiminginfo
					= &samsung_s6d7aa0x01_1280_800_video_timing_info;
		panelstruct->panelresetseq
					= &samsung_s6d7aa0x01_1280_800_video_reset_seq;
		panelstruct->backlightinfo = &samsung_s6d7aa0x01_1280_800_video_backlight;
        panelstruct->paneldata->panel_with_enable_gpio = 1 ;
		pinfo->mipi.panel_cmds
					= samsung_s6d7aa0x01_1280_800_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= SAMSUNG_S6D7AA0X01_1280_800_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				samsung_s6d7aa0x01_1280_800_video_timings, TIMING_SIZE);
        pinfo->mipi.signature = SAMSUNG_S6D7AA0X01_VIDEO_SIGNATURE;
		pinfo->mipi.ic_type = SAMSUNG_S6D7AA0X01_VIDEO_IC_TYPE;
		pinfo->mipi.lcd_adc = SAMSUNG_S6D7AA0X01_VIDEO_LCD_ADC_STATUS;
		pinfo->mipi.adc_max = SAMSUNG_S6D7AA0X01_VIDEO_LCD_ADC_MAX;
		pinfo->mipi.adc_min = SAMSUNG_S6D7AA0X01_VIDEO_LCD_ADC_MIN;
		break;
    case BP080WX1_S6D7AA0X01_1280_800_VIDEO_PANEL:
		panelstruct->paneldata    = &bp080wx1_s6d7aa0x01_1280_800_video_panel_data;
		panelstruct->panelres     = &bp080wx1_s6d7aa0x01_1280_800_video_panel_res;
		panelstruct->color        = &bp080wx1_s6d7aa0x01_1280_800_video_color;
		panelstruct->videopanel   = &bp080wx1_s6d7aa0x01_1280_800_video_video_panel;
		panelstruct->commandpanel = &bp080wx1_s6d7aa0x01_1280_800_video_command_panel;
		panelstruct->state        = &bp080wx1_s6d7aa0x01_1280_800_video_state;
		panelstruct->laneconfig   = &bp080wx1_s6d7aa0x01_1280_800_video_lane_config;
		panelstruct->paneltiminginfo
					= &bp080wx1_s6d7aa0x01_1280_800_video_timing_info;
		panelstruct->panelresetseq
					= &bp080wx1_s6d7aa0x01_1280_800_video_reset_seq;
		panelstruct->backlightinfo = &bp080wx1_s6d7aa0x01_1280_800_video_backlight;
        panelstruct->paneldata->panel_with_enable_gpio = 1 ;
		pinfo->mipi.panel_cmds
					= bp080wx1_s6d7aa0x01_1280_800_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= BP080WX1_S6D7AA0X01_1280_800_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				bp080wx1_s6d7aa0x01_1280_800_video_timings, TIMING_SIZE);
        pinfo->mipi.signature = BP080WX1_S6D7AA0X01_VIDEO_SIGNATURE;
		pinfo->mipi.ic_type = BP080WX1_S6D7AA0X01_VIDEO_IC_TYPE;
		pinfo->mipi.lcd_adc = BP080WX1_S6D7AA0X01_VIDEO_LCD_ADC_STATUS;
		pinfo->mipi.adc_max = BP080WX1_S6D7AA0X01_VIDEO_LCD_ADC_MAX;
		pinfo->mipi.adc_min = BP080WX1_S6D7AA0X01_VIDEO_LCD_ADC_MIN;
		break;		
	case BOE_ILI6336_WXGA_VIDEO_PANEL:                            
		panelstruct->paneldata    = &boe_ili6336_wxga_video_panel_data;   
		panelstruct->panelres     = &boe_ili6336_wxga_video_panel_res;    
		panelstruct->color        = &boe_ili6336_wxga_video_color;        
		panelstruct->videopanel   = &boe_ili6336_wxga_video_video_panel;  
		panelstruct->commandpanel = &boe_ili6336_wxga_video_command_panel;
		panelstruct->state        = &boe_ili6336_wxga_video_state;        
		panelstruct->laneconfig   = &boe_ili6336_wxga_video_lane_config;  
		panelstruct->paneltiminginfo                                         
					 = &boe_ili6336_wxga_video_timing_info;                     
		panelstruct->panelresetseq                                           
					= &boe_ili6336_wxga_video_panel_reset_seq;                  
		panelstruct->backlightinfo = &boe_ili6336_wxga_video_backlight; 
		panelstruct->paneldata->panel_with_enable_gpio = 1 ;			
		pinfo->mipi.panel_cmds                                               
					= boe_ili6336_wxga_video_on_command;                        
		pinfo->mipi.num_of_panel_cmds                                        
					= BOE_ILI_WXGA_VIDEO_ON_COMMAND;                        
		memcpy(phy_db->timing,                                               
				boe_ili6336_wxga_video_timings, TIMING_SIZE);                 
		pinfo->mipi.signature = BOE_ILI_WXGA_VIDEO_SIGNATURE;         
		pinfo->mipi.lcd_adc = BOE_ILI_WXGA_VIDEO_ADC_STATUS;          
		pinfo->mipi.ic_type = BOE_ILI_WXGA_VIDEO_IC_TYPE;             
		pinfo->mipi.adc_max = BOE_ILI_WXGA_VIDEO_ADC_MAX;             
		pinfo->mipi.adc_min = BOE_ILI_WXGA_VIDEO_ADC_MIN;	
		break;
	case OTM1901A_BOOYI_AUO_FHD_550_VIDEO_PANEL:
		panelstruct->paneldata    = &booyi_otm1901a_1080p_5p5_video_panel_data;
		panelstruct->panelres     = &booyi_otm1901a_1080p_5p5_video_panel_res;
		panelstruct->color        = &booyi_otm1901a_1080p_5p5_video_color;
		panelstruct->videopanel   = &booyi_otm1901a_1080p_5p5_video_video_panel;
		panelstruct->commandpanel = &booyi_otm1901a_1080p_5p5_video_command_panel;
		panelstruct->state        = &booyi_otm1901a_1080p_5p5_video_state;
		panelstruct->laneconfig   = &booyi_otm1901a_1080p_5p5_video_lane_config;
		panelstruct->paneltiminginfo
					 = &booyi_otm1901a_1080p_5p5_video_timing_info;
		panelstruct->panelresetseq
					= &booyi_otm1901a_1080p_5p5_video_panel_reset_seq;
		panelstruct->backlightinfo = &booyi_otm1901a_1080p_5p5_video_backlight;
		pinfo->mipi.panel_cmds
					= booyi_otm1901a_1080p_5p5_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= BOOYI_OTM1901A_1080P_5P5_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				booyi_otm1901a_1080p_5p5_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = BOOYI_OTM1901A_1080P_5P5_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = BOOYI_OTM1901A_1080P_5P5_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = BOOYI_OTM1901A_1080P_5P5_VIDEO_ADC_MIN;
		break;  
	case OTM1901A_GONGTAI_AUO_FHD_550_VIDEO_PANEL:
		panelstruct->paneldata    = &gongtai_otm1901a_1080p_5p5_video_panel_data;
		panelstruct->panelres     = &gongtai_otm1901a_1080p_5p5_video_panel_res;
		panelstruct->color        = &gongtai_otm1901a_1080p_5p5_video_color;
		panelstruct->videopanel   = &gongtai_otm1901a_1080p_5p5_video_video_panel;
		panelstruct->commandpanel = &gongtai_otm1901a_1080p_5p5_video_command_panel;
		panelstruct->state        = &gongtai_otm1901a_1080p_5p5_video_state;
		panelstruct->laneconfig   = &gongtai_otm1901a_1080p_5p5_video_lane_config;
		panelstruct->paneltiminginfo
					 = &gongtai_otm1901a_1080p_5p5_video_timing_info;
		panelstruct->panelresetseq
					= &gongtai_otm1901a_1080p_5p5_video_panel_reset_seq;
		panelstruct->backlightinfo = &gongtai_otm1901a_1080p_5p5_video_backlight;
		pinfo->mipi.panel_cmds
					= gongtai_otm1901a_1080p_5p5_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= GONGTAI_OTM1901A_1080P_5P5_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				gongtai_otm1901a_1080p_5p5_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = GONGTAI_OTM1901A_1080P_5P5_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = GONGTAI_OTM1901A_1080P_5P5_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = GONGTAI_OTM1901A_1080P_5P5_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = GONGTAI_OTM1901A_1080P_5P5_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = GONGTAI_OTM1901A_1080P_5P5_VIDEO_ADC_MIN;
		break;  		
	case NT35596_TXD_AUO_FHD_550_VIDEO_PANEL:
		panelstruct->paneldata    = &txd_nt35596_1080p_video_panel_data;
		panelstruct->panelres     = &txd_nt35596_1080p_video_panel_res;
		panelstruct->color        = &txd_nt35596_1080p_video_color;
		panelstruct->videopanel   = &txd_nt35596_1080p_video_video_panel;
		panelstruct->commandpanel = &txd_nt35596_1080p_video_command_panel;
		panelstruct->state        = &txd_nt35596_1080p_video_state;
		panelstruct->laneconfig   = &txd_nt35596_1080p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &txd_nt35596_1080p_video_timing_info;
		panelstruct->panelresetseq
					= &txd_nt35596_1080p_video_panel_reset_seq;
		panelstruct->backlightinfo = &txd_nt35596_1080p_video_backlight;
		pinfo->mipi.panel_cmds
					= txd_nt35596_1080p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= TXD_NT35596_1080P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				txd_nt35596_1080p_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = TXD_NT35596_1080P_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = TXD_NT35596_1080P_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = TXD_NT35596_1080P_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = TXD_NT35596_1080P_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = TXD_NT35596_1080P_VIDEO_ADC_MIN;
		break;
	case ST7703_HXGD_HD_5P5_VIDEO_PANEL:
		panelstruct->paneldata    = &hxgd_st7703_hd_5p5_video_panel_data;
		panelstruct->panelres     = &hxgd_st7703_hd_5p5_video_panel_res;
		panelstruct->color        = &hxgd_st7703_hd_5p5_video_color;
		panelstruct->videopanel   = &hxgd_st7703_hd_5p5_video_video_panel;
		panelstruct->commandpanel = &hxgd_st7703_hd_5p5_video_command_panel;
		panelstruct->state        = &hxgd_st7703_hd_5p5_video_state;
		panelstruct->laneconfig   = &hxgd_st7703_hd_5p5_video_lane_config;
		panelstruct->paneltiminginfo
					 = &hxgd_st7703_hd_5p5_video_timing_info;
		panelstruct->panelresetseq
					= &hxgd_st7703_hd_5p5_video_panel_reset_seq;
		panelstruct->backlightinfo = &hxgd_st7703_hd_5p5_video_backlight;
		pinfo->mipi.panel_cmds
					= hxgd_st7703_hd_5p5_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= HXGD_ST7703_HD_5P5_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				h8394d_txd_hd_innolux_hd_550_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = HXGD_ST7703_HD_5P5_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = HXGD_ST7703_HD_5P5_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = HXGD_ST7703_HD_5P5_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = HXGD_ST7703_HD_5P5_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = HXGD_ST7703_HD_5P5_VIDEO_ADC_MIN;
		break;		
	case H8394D_TXD_HD_INNOLUX_VIDEO_PANEL:
		panelstruct->paneldata    = &h8394d_txd_hd_innolux_hd_550_video_panel_data;
		panelstruct->panelres     = &h8394d_txd_hd_innolux_hd_550_video_panel_res;
		panelstruct->color        = &h8394d_txd_hd_innolux_hd_550_video_color;
		panelstruct->videopanel   = &h8394d_txd_hd_innolux_hd_550_video_video_panel;
		panelstruct->commandpanel = &h8394d_txd_hd_innolux_hd_550_video_command_panel;
		panelstruct->state        = &h8394d_txd_hd_innolux_hd_550_video_state;
		panelstruct->laneconfig   = &h8394d_txd_hd_innolux_hd_550_video_lane_config;
		panelstruct->paneltiminginfo
					 = &h8394d_txd_hd_innolux_hd_550_video_timing_info;
		panelstruct->panelresetseq
					= &h8394d_txd_hd_innolux_hd_550_video_panel_reset_seq;
		panelstruct->backlightinfo = &h8394d_txd_hd_innolux_hd_550_video_backlight;
		pinfo->mipi.panel_cmds
					= h8394d_txd_hd_innolux_hd_550_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= H8394D_TXD_HD_INNOLUX_550_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				h8394d_txd_hd_innolux_hd_550_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = H8394D_TXD_HD_INNOLUX_550_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = H8394D_TXD_HD_INNOLUX_550_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = H8394D_TXD_HD_INNOLUX_550_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = H8394D_TXD_HD_INNOLUX_550_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = H8394D_TXD_HD_INNOLUX_550_VIDEO_ADC_MIN;
		break;
	case H8394F_JD_HD_AUO_VIDEO_PANEL:
		panelstruct->paneldata    = &h8394f_jd_hd_auo_hd_550_video_panel_data;
		panelstruct->panelres     = &h8394f_jd_hd_auo_hd_550_video_panel_res;
		panelstruct->color        = &h8394f_jd_hd_auo_hd_550_video_color;
		panelstruct->videopanel   = &h8394f_jd_hd_auo_hd_550_video_video_panel;
		panelstruct->commandpanel = &h8394f_jd_hd_auo_hd_550_video_command_panel;
		panelstruct->state        = &h8394f_jd_hd_auo_hd_550_video_state;
		panelstruct->laneconfig   = &h8394f_jd_hd_auo_hd_550_video_lane_config;
		panelstruct->paneltiminginfo
					 = &h8394f_jd_hd_auo_hd_550_video_timing_info;
		panelstruct->panelresetseq
					= &h8394f_jd_hd_auo_hd_550_video_panel_reset_seq;
		panelstruct->backlightinfo = &h8394f_jd_hd_auo_hd_550_video_backlight;
		pinfo->mipi.panel_cmds
					= h8394f_jd_hd_auo_hd_550_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= H8394F_JD_HD_AUO_550_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				h8394f_jd_hd_auo_hd_550_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = H8394F_JD_HD_AUO_550_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = H8394F_JD_HD_AUO_550_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = H8394F_JD_HD_AUO_550_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = H8394F_JD_HD_AUO_550_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = H8394F_JD_HD_AUO_550_VIDEO_ADC_MIN;
		break;
	case OTM1284_LEAD_HD_CPT_VIDEO_PANEL:
		panelstruct->paneldata    = &otm1284_lead_hd_cpt_hd_550_video_panel_data;
		panelstruct->panelres     = &otm1284_lead_hd_cpt_hd_550_video_panel_res;
		panelstruct->color        = &otm1284_lead_hd_cpt_hd_550_video_color;
		panelstruct->videopanel   = &otm1284_lead_hd_cpt_hd_550_video_video_panel;
		panelstruct->commandpanel = &otm1284_lead_hd_cpt_hd_550_video_command_panel;
		panelstruct->state        = &otm1284_lead_hd_cpt_hd_550_video_state;
		panelstruct->laneconfig   = &otm1284_lead_hd_cpt_hd_550_video_lane_config;
		panelstruct->paneltiminginfo
					 = &otm1284_lead_hd_cpt_hd_550_video_timing_info;
		panelstruct->panelresetseq
					= &otm1284_lead_hd_cpt_hd_550_video_panel_reset_seq;
		panelstruct->backlightinfo = &otm1284_lead_hd_cpt_hd_550_video_backlight;
		pinfo->mipi.panel_cmds
					= otm1284_lead_hd_cpt_hd_550_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= OTM1284_LEAD_HD_CPT_550_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				otm1284_lead_hd_cpt_hd_550_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = OTM1284_LEAD_HD_CPT_550_VIDEO_SIGNATURE;
		pinfo->mipi.lcd_adc = OTM1284_LEAD_HD_CPT_550_VIDEO_ADC_STATUS;
		pinfo->mipi.ic_type = OTM1284_LEAD_HD_CPT_550_VIDEO_IC_TYPE;
		pinfo->mipi.adc_max = OTM1284_LEAD_HD_CPT_550_VIDEO_ADC_MAX;
		pinfo->mipi.adc_min = OTM1284_LEAD_HD_CPT_550_VIDEO_ADC_MIN;
		break;
   case COMMON_NT71410_1920_1200_VIDEO_PANEL:
		panelstruct->paneldata    = &common_nt71410_1920_1200_video_panel_data;
		panelstruct->panelres     = &common_nt71410_1920_1200_video_panel_res;
		panelstruct->color        = &common_nt71410_1920_1200_video_color;
		panelstruct->videopanel   = &common_nt71410_1920_1200_video_video_panel;
		panelstruct->commandpanel = &common_nt71410_1920_1200_video_command_panel;
		panelstruct->state        = &common_nt71410_1920_1200_video_state;
		panelstruct->laneconfig   = &common_nt71410_1920_1200_video_lane_config;
		panelstruct->paneltiminginfo
					= &common_nt71410_1920_1200_video_timing_info;
		panelstruct->panelresetseq
					= &common_nt71410_1920_1200_video_reset_seq;
		panelstruct->backlightinfo = &common_nt71410_1920_1200_video_backlight;
    //panelstruct->paneldata->panel_with_enable_gpio = 1 ;
		pinfo->mipi.panel_cmds
					= common_nt71410_1920_1200_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= COMMON_NT71410_1920_1200_VIDEO_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				common_nt71410_1920_1200_video_timings, TIMING_SIZE);
        pinfo->mipi.signature = COMMON_NT71410_1920_1200_SIGNATURE;
		pinfo->mipi.ic_type = COMMON_NT71410_1920_1200_IC_TYPE;
		pinfo->mipi.lcd_adc = COMMON_NT71410_1920_1200_LCD_ADC_STATUS;
		pinfo->mipi.adc_max = COMMON_NT71410_1920_1200_LCD_ADC_MAX;
		pinfo->mipi.adc_min = COMMON_NT71410_1920_1200_LCD_ADC_MIN;
		//pinfo->mipi.force_clk_lane_hs=true;
		break;
	case NT35521S_720P_VIDEO_PANEL:
		dprintf(CRITICAL, "  enter display NT35521S_720P_VIDEO_PANEL\n");
		panelstruct->paneldata    = &nt35521s_720p_video_panel_data;
		panelstruct->panelres     = &nt35521s_720p_video_panel_res;
		panelstruct->color        = &nt35521s_720p_video_color;
		panelstruct->videopanel   = &nt35521s_720p_video_video_panel;
		panelstruct->commandpanel = &nt35521s_720p_video_command_panel;
		panelstruct->state        = &nt35521s_720p_video_state;
		panelstruct->laneconfig   = &nt35521s_720p_video_lane_config;
		panelstruct->paneltiminginfo
					= &nt35521s_720p_video_timing_info;
		panelstruct->panelresetseq
					= &nt35521s_720p_video_reset_seq;
		panelstruct->backlightinfo = &nt35521s_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= nt35521s_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= ARRAY_SIZE(nt35521s_720p_video_on_command);
		memcpy(phy_db->timing,
				nt35521s_720p_video_timings, TIMING_SIZE);
    pinfo->mipi.signature = NT35521S_1280_800_SIGNATURE;
		pinfo->mipi.ic_type = NT35521S_1280_800_IC_TYPE;
		pinfo->mipi.lcd_adc = NT35521S_1280_800_LCD_ADC_STATUS;
		pinfo->mipi.adc_max = NT35521S_1280_800_LCD_ADC_MAX;
		pinfo->mipi.adc_min = NT35521S_1280_800_LCD_ADC_MIN;				
		break;


	case UNKNOWN_PANEL:
	default:
		memset(panelstruct, 0, sizeof(struct panel_struct));
		memset(pinfo->mipi.panel_cmds, 0, sizeof(struct mipi_dsi_cmd));
		pinfo->mipi.num_of_panel_cmds = 0;
		memset(phy_db->timing, 0, TIMING_SIZE);
		pan_type = PANEL_TYPE_UNKNOWN;
		break;
	}
	return pan_type;
}

uint32_t oem_panel_max_auto_detect_panels()
{
        return target_panel_auto_detect_enabled() ?
                        DISPLAY_MAX_PANEL_DETECTION : 0;
}

int oem_panel_select(const char *panel_name, struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	uint32_t hw_id = board_hardware_id();
	uint32_t hw_subtype = board_hardware_subtype();
	int32_t panel_override_id;
	uint32_t target_id, plat_hw_ver_major;

	if (panel_name) {
		panel_override_id = panel_name_to_id(supp_panels,
				ARRAY_SIZE(supp_panels), panel_name);

		if (panel_override_id < 0) {
			dprintf(CRITICAL, "Not able to search the panel:%s\n",
					 panel_name + strspn(panel_name, " "));
		} else if (panel_override_id < UNKNOWN_PANEL) {
			/* panel override using fastboot oem command */
			panel_id = panel_override_id;

			dprintf(INFO, "OEM panel override:%s\n",
					panel_name + strspn(panel_name, " "));
			goto panel_init;
		}
	}

	hw_id=HW_PLATFORM_MTP;
	switch (hw_id) {
	case HW_PLATFORM_MTP:
		if (1==0) {
			panel_id = JDI_FHD_VIDEO_PANEL;
		} else {
#ifdef BOOT_FEATURE_P1071
			panel_id = SAMSUNG_S6D7AA0X01_1280_800_VIDEO_PANEL;
			switch (auto_pan_loop){                
				case 0:
					panel_id = SAMSUNG_S6D7AA0X01_1280_800_VIDEO_PANEL;					
				break;
				case 1:
					panel_id =  BOE_ILI6336_WXGA_VIDEO_PANEL;
				break;
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
#ifdef BOOT_FEATURE_A2001
			panel_id = OTM1901A_BOOYI_AUO_FHD_550_VIDEO_PANEL;
			switch (auto_pan_loop){                
				case 0:
					panel_id = OTM1901A_BOOYI_AUO_FHD_550_VIDEO_PANEL;					
				break;
				case 1:
					panel_id = NT35596_TXD_AUO_FHD_550_VIDEO_PANEL;					
				break;
				case 2:
					panel_id = OTM1901A_GONGTAI_AUO_FHD_550_VIDEO_PANEL;					
				break;				
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
#if defined(BOOT_FEATURE_A3001) || defined(BOOT_FEATURE_A3002)
			panel_id = H8394D_TXD_HD_INNOLUX_VIDEO_PANEL;
			switch (auto_pan_loop){                
				case 0:
					panel_id = H8394D_TXD_HD_INNOLUX_VIDEO_PANEL;
					break;
				case 1:
					panel_id = H8394F_JD_HD_AUO_VIDEO_PANEL;
					break;
				case 2:
					panel_id = OTM1284_LEAD_HD_CPT_VIDEO_PANEL;						
					break;
				case 3: // by skj
					panel_id = ST7703_HXGD_HD_5P5_VIDEO_PANEL;
					break;
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
#if defined(BOOT_FEATURE_Q10)
			panel_id = COMMON_NT71410_1920_1200_VIDEO_PANEL;
			switch (auto_pan_loop){                
				case 0:
					panel_id = COMMON_NT71410_1920_1200_VIDEO_PANEL;
				break;
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
#if defined(BOOT_FEATURE_Q10HD)
			panel_id = NT35521S_720P_VIDEO_PANEL;
			switch (auto_pan_loop){
				case 0:
					panel_id = NT35521S_720P_VIDEO_PANEL;
				break;				                
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
#ifdef BOOT_FEATURE_Q8HD
			panel_id = BP080WX1_S6D7AA0X01_1280_800_VIDEO_PANEL;
			switch (auto_pan_loop){                
				case 0:
					panel_id = BP080WX1_S6D7AA0X01_1280_800_VIDEO_PANEL;					
				break;
				default:
					panel_id = UNKNOWN_PANEL;
					dprintf(CRITICAL, "Unknown panel\n");
			}
			auto_pan_loop++;
			dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",
                                                    panel_id,auto_pan_loop);
#endif
		}
		dprintf(CRITICAL,"Panle_id is %d,auto_pan_loop is %d\n",panel_id,auto_pan_loop);
		break;
	default:
		dprintf(CRITICAL, "Display not enabled for %d HW type\n",
			hw_id);
		return PANEL_TYPE_UNKNOWN;
	}

panel_init:
	/* Set LDO mode */
	if (platform_is_msm8939() || platform_is_msm8929() || (hw_id == HW_PLATFORM_QRD))
		phy_db->regulator_mode = DSI_PHY_REGULATOR_LDO_MODE;

	pinfo->pipe_type = MDSS_MDP_PIPE_TYPE_RGB;
	return init_panel_data(panelstruct, pinfo, phy_db);
}
