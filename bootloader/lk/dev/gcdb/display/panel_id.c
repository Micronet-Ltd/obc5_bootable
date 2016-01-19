/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
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
 *
 */


#include <stdint.h>
#include <msm_panel.h>
#include <mipi_dsi.h>
#include <sys/types.h>
#include <err.h>
#include <reg.h>
#include <mdp5.h>
#include <endian.h>
#include <debug.h>
#include <kernel/timer.h>
#include <platform/iomap.h>
#include <target/display.h>
#include <platform/gpio.h>
#include <pm8x41_adc.h>

/*Modify for logo display in lk begined*/
extern int mipi_dsi_cmd_bta_sw_trigger(void);

/********************************************************************************
 ****get lcd panel id status
 ********************************************************************************/
uint32_t get_lcd_adc(void)
{
	uint32_t lcd_val;

	pm8x41_enable_mpp_as_adc(1); 
	lcd_val = pm8x41_adc_channel_read(MPP_2_CHAN_ID);
		
	dprintf(INFO, "%s:lcd_val = %d!\n",__func__,lcd_val);

	return lcd_val;
}
/********************************************************************************
 ****get r63311 panel ic name
 ********************************************************************************/
static char mipi_panel_manufacture_id_r63311[4] = {0xbf, 0x00, 0x14, 0xA0}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_manufacture_id_r63311_cmd =
{sizeof(mipi_panel_manufacture_id_r63311), mipi_panel_manufacture_id_r63311};

static int mipi_r63311_id_read(void)
{	  
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_r63311_cmd, 1);
	mdelay(50);//shiyan from 1
	mipi_dsi_cmds_rx(&rp, 1);
	 
	lp = (uint32_t *)rp;
		 
		 data = (uint32_t)*lp;
		 data = ntohl(data);
		 dprintf(INFO, "mipi_r63311_id_read() data=0x%x\n",data);
		 data = data &0x000000ff;
		// data=data>>16;    
		 return data;
 }
/********************************************************************************
 ****get himax panel ic name
 ********************************************************************************/
static char hx8369a_extend_cmd_enable[8] = {
	0x04, 0x00, 0x29, 0xC0,
	0xB9, 0xFF, 0x83, 0x94
};
static char hx8379_extend_cmd_enable[8] = {
	0x04, 0x00, 0x29, 0xC0,
	0xB9, 0xFF, 0x83, 0x79
};
static char mipi_panel_manufacture_id[4] = 
      {0xF4, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_manufacture_id_cmd =
    {sizeof(mipi_panel_manufacture_id), mipi_panel_manufacture_id};
static struct mipi_dsi_cmd hx8369a_extend_cmd_enable_cmd =
    {sizeof(hx8369a_extend_cmd_enable), hx8369a_extend_cmd_enable};
static struct mipi_dsi_cmd hx8379_extend_cmd_enable_cmd =
    {sizeof(hx8379_extend_cmd_enable), hx8379_extend_cmd_enable};
static uint32_t mipi_hx8394a01_read_id(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data;
    mipi_dsi_cmds_tx(&hx8369a_extend_cmd_enable_cmd, 1);
    mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_cmd, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(SPEW, "mipi_hx8369a_manufacture_id() data=0x%x\n",data);
    data = data &0xff0000;
    data=data>>16;   
    return data;
}
static uint32_t mipi_hx8379_read_id(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data;
    mipi_dsi_cmds_tx(&hx8379_extend_cmd_enable_cmd, 1);
    mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_cmd, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(SPEW, "mipi_hx8369a_manufacture_id() data=0x%x\n",data);
    data = data &0xff0000;
    data=data>>16;   
    return data;
}
static char hx8389b_extend_cmd_enable[8] = {
	0x04, 0x00, 0x29, 0xC0,
	0xB9, 0xFF, 0x83, 0x89
};
static char mipi_panel_hx8389b_manufacture_id[4] = 
      {0xDA, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_hx8389b_manufacture_id_cmd =
    {sizeof(mipi_panel_hx8389b_manufacture_id), mipi_panel_hx8389b_manufacture_id};
static struct mipi_dsi_cmd hx8389b_extend_cmd_enable_cmd =
    {sizeof(hx8389b_extend_cmd_enable), hx8389b_extend_cmd_enable};
static uint32_t mipi_hx8389b_read_id(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data;
    mipi_dsi_cmds_tx(&hx8389b_extend_cmd_enable_cmd, 1);
    mipi_dsi_cmds_tx(&mipi_panel_hx8389b_manufacture_id_cmd, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(SPEW, "mipi_hx8369a_manufacture_id() data=0x%x\n",data);
    data = data &0xff0000;
    data=data>>16;   
    return data;
}
/********************************************************************************
 ****get xuyaokeji panel ic name
 ********************************************************************************/
static char mipi_panel_manufacture_id_xuyaokeji[4] = {0xA1, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
static char mipi_panel_manufacture_id_xuyaokeji_continue_read[4] = {0xA8, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_manufacture_id_xuyaokeji_cmd =
{sizeof(mipi_panel_manufacture_id_xuyaokeji), mipi_panel_manufacture_id_xuyaokeji };

static struct mipi_dsi_cmd mipi_panel_manufacture_continue_read_id_xuyaokeji_cmd =
{sizeof(mipi_panel_manufacture_id_xuyaokeji_continue_read), mipi_panel_manufacture_id_xuyaokeji_continue_read};

static uint32_t mipi_xuyaokeji_otm_manufacture_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data,ret_data; 
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_xuyaokeji_cmd, 1);	 
	udelay(200);
	//mipi_dsi_cmd_bta_sw_trigger();
	mipi_dsi_cmds_rx(&rp,2);
	//udelay(10);	
	lp = (uint32_t *)rp;
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(SPEW, "mipi_xuyaokeji_otm_id_read(); the 1 byte data=0x%x\n",data);
	data = data &0xff0000;
	ret_data=data<<8;	
	
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_continue_read_id_xuyaokeji_cmd, 1);   
	udelay(200);
	//mipi_dsi_cmd_bta_sw_trigger();
	mipi_dsi_cmds_rx(&rp,2);
	//udelay(10);	
	lp = (uint32_t *)rp;
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(SPEW, "mipi_xuyaokeji_otm_id_read(); the 2 byte data=0x%x\n",data);
	data = data &0xff0000;
	ret_data|=data;   
	
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_continue_read_id_xuyaokeji_cmd, 1);   
	udelay(200);
	//mipi_dsi_cmd_bta_sw_trigger();
	mipi_dsi_cmds_rx(&rp,2);
	//udelay(10);	
	lp = (uint32_t *)rp;
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(SPEW, "mipi_xuyaokeji_otm_id_read(); the 3 byte data=0x%x\n",data);
	data = data &0xff0000;
	ret_data|=data>>8;	 
	
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_continue_read_id_xuyaokeji_cmd, 1);   
	udelay(200);
	//mipi_dsi_cmd_bta_sw_trigger();
	mipi_dsi_cmds_rx(&rp,2);
	//udelay(10);	
	lp = (uint32_t *)rp;
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(SPEW, "mipi_xuyaokeji_otm_id_read(); the 4 byte data=0x%x\n",data);
	data = data &0xff0000;
	ret_data|=data>>16; 
    ret_data= ret_data &0x0000ffff;  
	dprintf(SPEW, "mipi_xuyaokeji_otm_id_read(ret); the  panel id ret_data=0x%x\n",ret_data);
	return ret_data; 
}

/********************************************************************************
 ****get novatek panel ic name
 ********************************************************************************/
static char novatek_read_back_count_set_cmd[] = {
	 0x02,0x00,0x37,0x80
};
static char novatek_nop_cmd[] = {
	 0x01,0x00,0x29,0xc0,
        0x00,0xff,0xff,0xff,
        
};
static char novatek_page1_set_cmd[] = {
	 0x06,0x00,0x29,0xc0,
        0xF0,0x55,0xAA,0x52,
        0x08,0x01,0xFF,0xff
};
static struct mipi_dsi_cmd novatek_read_back_count_set[] =
    {
    {sizeof(novatek_read_back_count_set_cmd), novatek_read_back_count_set_cmd}
    };
static struct mipi_dsi_cmd novatek_page1_set[] =
    {
    {sizeof(novatek_page1_set_cmd), novatek_page1_set_cmd}
    };
static struct mipi_dsi_cmd novatek_nop[] =
    {
    {sizeof(novatek_nop_cmd), novatek_nop_cmd},
    };
static char mipi_panel_manufacture_id_novatek[4] = {0xc5, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_manufacture_id_novatek_cmd =
    {sizeof(mipi_panel_manufacture_id_novatek), mipi_panel_manufacture_id_novatek};
static int mipi_novatek_id_read(void)
{	 
		char rec_buf[24];
		char *rp = rec_buf;
		uint32_t *lp, data;
		writel(0x10000000, DSI_COMMAND_MODE_DMA_CTRL);
	       mipi_dsi_cmds_tx(novatek_nop, ARRAY_SIZE(novatek_nop));
	       writel(0x14000000, DSI_COMMAND_MODE_DMA_CTRL);
		mipi_dsi_cmds_tx(novatek_page1_set, ARRAY_SIZE(novatek_page1_set));
		mipi_dsi_cmds_tx(novatek_read_back_count_set, ARRAY_SIZE(novatek_read_back_count_set));
		mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_novatek_cmd, 1);
		mdelay(50);
		mipi_dsi_cmds_rx(&rp, 1);
	
		lp = (uint32_t *)rp;
		
		data = (uint32_t)*lp;
		data = ntohl(data);
		dprintf(SPEW, "mipi_novatek_id_read() data=0x%x\n",data);
		data = data &0x00ffff00;
		data=data>>8;	  
		return data;
}

/********************************************************************************
 ****get nt35521 panel ic name
********************************************************************************/
static char nt35521_cmd0[] = {0x01,0x00,0x29,0xc0,0x00,0xff,0xff,0xff,};
static char nt35521_cmd1[] = {0x06,0x00,0x29,0xc0,0xF0,0x55,0xAA,0x52,0x08,0x01,0xFF,0xff};

static struct mipi_dsi_cmd nt35521_extend_cmd_enable_cmd[] =
{
	{sizeof(nt35521_cmd1), nt35521_cmd1}
};

static struct mipi_dsi_cmd nt35521_nop[] =
{
    {sizeof(nt35521_cmd0), nt35521_cmd0},  
};

static char mipi_panel_manufacture_id_nt35521[4] = {0xc5, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_manufacture_id_nt35521_cmd =
{sizeof(mipi_panel_manufacture_id_nt35521), mipi_panel_manufacture_id_nt35521};

static int mipi_nt35521_id_read(void)
{	 
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	writel(0x10000000, DSI_COMMAND_MODE_DMA_CTRL);
    mipi_dsi_cmds_tx(nt35521_nop, ARRAY_SIZE(nt35521_nop));
    writel(0x14000000, DSI_COMMAND_MODE_DMA_CTRL);
	mipi_dsi_cmds_tx(nt35521_extend_cmd_enable_cmd, ARRAY_SIZE(nt35521_extend_cmd_enable_cmd));
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_nt35521_cmd, 1);
	mdelay(50);//shiyan from 1
	mipi_dsi_cmds_rx(&rp, 1);

	lp = (uint32_t *)rp;
	
	data = (uint32_t)*lp;
	data = ntohl(data);
	data = data &0xff0000;
	data=data>>16;	
	
	dprintf(INFO, "mipi_nt35521_manufacture_id() data=0x%x\n",data);
	return data;
}

/********************************************************************************
 ****get nt35596 panel ic name
********************************************************************************/
static char nt35596_cmd0[] = {0x01,0x00,0x29,0xc0,0xff,0x00,0xff,0xff};

static struct mipi_dsi_cmd nt35596_nop[] =
{
    {sizeof(nt35596_cmd0), nt35596_cmd0},
};

static char mipi_panel_manufacture_id_nt35596[4] = {0xf4, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_manufacture_id_nt35596_cmd =
{sizeof(mipi_panel_manufacture_id_nt35596), mipi_panel_manufacture_id_nt35596};

static int mipi_nt35596_id_read(void)
{	 
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	writel(0x10000000, DSI_COMMAND_MODE_DMA_CTRL);
    mipi_dsi_cmds_tx(novatek_nop, ARRAY_SIZE(novatek_nop));
    writel(0x14000000, DSI_COMMAND_MODE_DMA_CTRL);
	mipi_dsi_cmds_tx(&mipi_panel_manufacture_id_nt35596_cmd, 1);
	mdelay(50);//shiyan from 1
	mipi_dsi_cmds_rx(&rp, 1);

	lp = (uint32_t *)rp;
	
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(INFO, "mipi_nt35596_manufacture_id() data=0x%x\n",data);
	data = data &0xff0000;
	data=data>>16;

	dprintf(INFO, "mipi_nt35596_manufacture_id() data=0x%x\n",data);
	return data;
}

/********************************************************************************
 ****get ilitek panel ic name
 ********************************************************************************/
static char mipi_panel_ili9806e_page1[12] = {
0x06,0x00,0x29,0xc0,
0xFF,0xFF,0x98,0x06,
0x04,0x01,0xff,0xff
};
static char mipi_panel_ili9806e_readid[4] = {
  0x00, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili9806e_readid1[4] = {
  0x01, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili9806e_readid2[4] = {
  0x02, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili9806e_ack0[4] = {
  0x04, 0x00, 0x37, 0x80}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_ili9806e_change_page[] =
    {
	{sizeof(mipi_panel_ili9806e_page1),mipi_panel_ili9806e_page1}
    };

static struct mipi_dsi_cmd mipi_panel_ili9806e_read[] =
    {
	{sizeof(mipi_panel_ili9806e_readid),mipi_panel_ili9806e_readid}
    };
static struct mipi_dsi_cmd mipi_panel_ili9806e_read1[] =
    {
	{sizeof(mipi_panel_ili9806e_readid1),mipi_panel_ili9806e_readid1}
    };
static struct mipi_dsi_cmd mipi_panel_ili9806e_read2[] =
    {
	{sizeof(mipi_panel_ili9806e_readid2),mipi_panel_ili9806e_readid2}
    };
static struct mipi_dsi_cmd mipi_panel_ili9806e_cmda[] =
    {
	{sizeof(mipi_panel_ili9806e_ack0), mipi_panel_ili9806e_ack0}
    };
static uint32_t mipi_ili9806e_read_status(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data;
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_change_page, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_read1, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_cmda, 1);	
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_read, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_cmda, 1);	
    udelay(10);
	mipi_dsi_cmd_bta_sw_trigger();
    mipi_dsi_cmds_rx(&rp, 4);
    udelay(10);
	
    lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
    data = data &0x000000ff;
	dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
	
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_read1, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_cmda, 1);	
    udelay(10);
	mipi_dsi_cmd_bta_sw_trigger();
    mipi_dsi_cmds_rx(&rp, 4);
    udelay(10);
	
    lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
    data = data &0x000000ff;
	dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
	
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_read2, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili9806e_cmda, 1);	
    udelay(10);
	mipi_dsi_cmd_bta_sw_trigger();
    mipi_dsi_cmds_rx(&rp, 4);
    udelay(10);
	
    lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
    data = data &0x000000ff;
	    dprintf(INFO, "mipi_ili9806_read_status() data=0x%x\n",data);
    //data=data>>8;   
    return data;
}

/********************************************************************************
 ****get rm68191 panel ic id
 ********************************************************************************/

static char mipi_panel_rm68191_page1_set[] ={
0x06,0x00,0x39,0xc0,
0xF0,0x55,0xAA,0x52,
0x08,0x01,0xff,0xff
};

static struct mipi_dsi_cmd mipi_panel_rm68191_page1_set_cmd =
{sizeof(mipi_panel_rm68191_page1_set), mipi_panel_rm68191_page1_set};

static char mipi_panel_rm68191_id_read[] = {0xC5, 0x00, 0x14, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_rm68191_id_read_cmd =
{sizeof(mipi_panel_rm68191_id_read), mipi_panel_rm68191_id_read};

static int mipi_rm68191_id_read(void)
{	  
    mdss_dsi_panel_reset(1);
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	mipi_dsi_cmds_tx(&mipi_panel_rm68191_page1_set_cmd, 1);
	mdelay(2);
	mipi_dsi_cmds_tx(&mipi_panel_rm68191_id_read_cmd, 1);
	mdelay(50);
	mipi_dsi_cmds_rx(&rp, 2);
	 
	lp = (uint32_t *)rp;
		 
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(INFO, "mipi_rm68191_id_read() data=0x%x\n",data);
	data = data &0x000000ff;
	// data=data>>16;    
	return data;
}
/********************************************************************************
 ****get rm68171 panel ic id
 ********************************************************************************/

static char mipi_panel_rm68171_page1_set[] ={
0x06,0x00,0x39,0xc0,
0xF0,0x55,0xAA,0x52,
0x08,0x01,0xff,0xff
};

static struct mipi_dsi_cmd mipi_panel_rm68171_page1_set_cmd =
{sizeof(mipi_panel_rm68171_page1_set), mipi_panel_rm68171_page1_set};

static char mipi_panel_rm68171_id_read[] = {0xC5, 0x00, 0x14, 0xA0}; /* DTYPE_DCS_READ */

static struct mipi_dsi_cmd mipi_panel_rm68171_id_read_cmd =
{sizeof(mipi_panel_rm68171_id_read), mipi_panel_rm68171_id_read};

static int mipi_rm68171_id_read(void)
{	  
    mdss_dsi_panel_reset(1);
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	mipi_dsi_cmds_tx(&mipi_panel_rm68171_page1_set_cmd, 1);
	mdelay(2);
	mipi_dsi_cmds_tx(&mipi_panel_rm68171_id_read_cmd, 1);
	mdelay(50);
	mipi_dsi_cmds_rx(&rp, 2);
	 
	lp = (uint32_t *)rp;
		 
	data = (uint32_t)*lp;
	data = ntohl(data);
	dprintf(INFO, "mipi_rm68171_id_read() data=0x%x\n",data);
	data = data &0x00ff0000;
	data=data>>16;    
	return data;
}

/********************************************************************************
 ****get r61318 panel ic id
 ********************************************************************************/
static char mipi_panel_r61318_enable[] ={0x04, 0x00,0x37,0x80}; 
static char mipi_panel_r61318_id_read[4] = {0xbf, 0x00, 0x14, 0xA0}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_r61318_enable_cmd =
{sizeof(mipi_panel_r61318_enable), mipi_panel_r61318_enable};
static struct mipi_dsi_cmd mipi_panel_r61318_id_read_cmd =
{sizeof(mipi_panel_r61318_id_read), mipi_panel_r61318_id_read};

static int mipi_r61318_read_id(void)
{
    mdss_dsi_panel_reset(1);
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data;
	mipi_dsi_cmds_tx(&mipi_panel_r61318_enable_cmd, 1);
	mipi_dsi_cmds_tx(&mipi_panel_r61318_id_read_cmd, 1);	
	mdelay(50);	
	mipi_dsi_cmds_rx(&rp,4);	 
	lp = (uint32_t *)rp;		 
	data = (uint32_t)*lp;
	dprintf(INFO, "mipi_r61318_id_read() data=0x%x\n",data);
	data = ntohl(data);
	dprintf(INFO, "mipi_r61318_id_read() data=0x%x\n",data);

	data = data &0x0000ffff;
	// data=data>>16;    
	return data;

}

/********************************************************************************
 **************                                 Add by jiao.shp                      ***************************
 **************          get samsung s6d7aa0x01  panel ic id            ***************************
 ********************************************************************************/
#define SAMSUNG_DELAY 0
static char samsung_s6d7aa0x01_video_on_cmd0[] = {
    0x03,0x00,0x39,0xC0,
    0xF0,0x5A,0x5A,0xFF,
};
static char samsung_s6d7aa0x01_video_on_cmd1[] = {
    0x03,0x00,0x39,0xC0,
    0xF1,0x5A,0x5A,0xFF,
};
static char samsung_s6d7aa0x01_video_on_cmd2[] = {
    0x03,0x00,0x39,0xC0,
    0xFC,0xA5,0xA5,0xFF,
};

 /* DTYPE_DCS_READ */
static char mipi_panel_samsung_s6d7aa0x01_id1_read[4] = {0xda,0x00,0x06,0xA0};
static char mipi_panel_samsung_s6d7aa0x01_id2_read[4] = {0xdb,0x00,0x06,0xA0}; 
static char mipi_panel_samsung_s6d7aa0x01_id3_read[4] = {0xdc,0x00,0x06,0xA0}; 

static struct mipi_dsi_cmd mipi_panel_samsung_s6d7aa0x01_enable_cmd[] = {
    {sizeof(samsung_s6d7aa0x01_video_on_cmd0), \
            samsung_s6d7aa0x01_video_on_cmd0,SAMSUNG_DELAY},
    {sizeof(samsung_s6d7aa0x01_video_on_cmd1), \
            samsung_s6d7aa0x01_video_on_cmd1,SAMSUNG_DELAY},
    {sizeof(samsung_s6d7aa0x01_video_on_cmd2), \
            samsung_s6d7aa0x01_video_on_cmd2,SAMSUNG_DELAY},
};

static struct mipi_dsi_cmd mipi_panel_samsung_s6d7aa0x01_id1_read_cmd =
{sizeof(mipi_panel_samsung_s6d7aa0x01_id1_read), \
        mipi_panel_samsung_s6d7aa0x01_id1_read,SAMSUNG_DELAY};
static struct mipi_dsi_cmd mipi_panel_samsung_s6d7aa0x01_id2_read_cmd =
{sizeof(mipi_panel_samsung_s6d7aa0x01_id2_read), \
        mipi_panel_samsung_s6d7aa0x01_id2_read,SAMSUNG_DELAY};
static struct mipi_dsi_cmd mipi_panel_samsung_s6d7aa0x01_id3_read_cmd =
{sizeof(mipi_panel_samsung_s6d7aa0x01_id3_read), \
        mipi_panel_samsung_s6d7aa0x01_id3_read,SAMSUNG_DELAY};

static int mipi_samsung_s6d7aa0x01_read_id(void)
{
	char rec_buf[24];
	char *rp = rec_buf;
	uint32_t *lp, data = 0,ic_id = 0;
    #define panel_magic_number1 0x6247
    #define panel_magic_number2 0x6248
    
	mipi_dsi_cmds_tx(mipi_panel_samsung_s6d7aa0x01_enable_cmd, 3);
	mipi_dsi_cmds_tx(&mipi_panel_samsung_s6d7aa0x01_id1_read_cmd, 1);	
	mdelay(50);	
	mipi_dsi_cmds_rx(&rp,1);

	lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    data = data &0x000000ff;
    dprintf(INFO,"Samsung ic id reg 1 is 0x%x\n",data);
    ic_id = data;
    
    mipi_dsi_cmds_tx(&mipi_panel_samsung_s6d7aa0x01_id2_read_cmd, 1);	
	mdelay(50);	
	mipi_dsi_cmds_rx(&rp,1);

	lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    data = data &0x000000ff;
    dprintf(INFO,"Samsung ic id reg 2 is 0x%x\n",data);
    ic_id |= data << 8;

    #if 0
    mipi_dsi_cmds_tx(&mipi_panel_samsung_s6d7aa0x01_id3_read_cmd, 1);	
	mdelay(50);	
	mipi_dsi_cmds_rx(&rp,1);

	lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    data = data &0x000000ff;
    dprintf(INFO,"Samsung ic id reg 3 is 0x%x\n",data);
    ic_id |= data << 16;
    #endif
    
    dprintf(INFO,"Samsung ic id is 0x%x\n",ic_id);

    if(0x1404 == ic_id){
        dprintf(INFO,"%s:panel ic is samsung s6d7aa0x01,\
        lcd module is bp080wx7-101\n",__func__);
        return panel_magic_number1;
    }
    else if(0x1212 == ic_id){
        dprintf(INFO,"%s:panel ic is samsung s6d7aa0x01,\
        lcd module is from AiXingShiJi\n",__func__);
        return panel_magic_number1;
    }
    else if(0x00 == ic_id){
        dprintf(INFO,"%s:panel ic is samsung s6d7aa0x01,\
        lcd module is claa080wq02xg\n",__func__);
        return panel_magic_number2;
    }
    else{
        dprintf(INFO,"%s:Unknow panel ic type\n",__func__);
        return 0xff;
    }         
}
static char fl11280_extend_cmd_enable[8] = {
	0x04, 0x00, 0x29, 0xC0,
	0xB9, 0xF1, 0x12, 0x80
};
static char mipi_panel_fl11280_manufacture_id[4] = 
      {0xDA, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
static char mipi_panel_fl11280_manufacture_id1[4] = 
      {0xDB, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
static char mipi_panel_fl11280_manufacture_id2[4] = 
      {0xDC, 0x00, 0x06, 0xA0}; /* DTYPE_DCS_READ */
      
static struct mipi_dsi_cmd mipi_panel_fl11280_manufacture_id_cmd =
    {sizeof(mipi_panel_fl11280_manufacture_id), mipi_panel_fl11280_manufacture_id};
 
static struct mipi_dsi_cmd mipi_panel_fl11280_manufacture_id_cmd1 =
    {sizeof(mipi_panel_fl11280_manufacture_id1), mipi_panel_fl11280_manufacture_id1};

static struct mipi_dsi_cmd mipi_panel_fl11280_manufacture_id_cmd2 =
    {sizeof(mipi_panel_fl11280_manufacture_id2), mipi_panel_fl11280_manufacture_id2};

static struct mipi_dsi_cmd fl11280_extend_cmd_enable_cmd =
    {sizeof(fl11280_extend_cmd_enable), fl11280_extend_cmd_enable};

static uint32_t mipi_fl11280_read_id(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data,ret_data; 
    mipi_dsi_cmds_tx(&fl11280_extend_cmd_enable_cmd, 1);
    mipi_dsi_cmds_tx(&mipi_panel_fl11280_manufacture_id_cmd, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);

    data = data &0xff0000;
    data=data>>16;   
    dprintf(INFO, "mipi_fl11280_read_id() data=0x%x\n",data);
     ret_data=data<<8;
     dprintf(INFO, "mipi_fl11280_read_id() ret_data=0x%x\n",ret_data);
  
     mipi_dsi_cmds_tx(&mipi_panel_fl11280_manufacture_id_cmd1, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);

    data = data &0xff0000;
    data=data>>16;   
    dprintf(INFO, "mipi_fl11280_read_id() data=0x%x\n",data);
      ret_data|=data;
   ret_data<<8;
    dprintf(INFO, "mipi_fl11280_read_id() ret_data=0x%x\n",ret_data);
    #if 0
    mipi_dsi_cmds_tx(&mipi_panel_fl11280_manufacture_id_cmd2, 1);
    mdelay(1);
    mipi_dsi_cmds_rx(&rp, 2);

    lp = (uint32_t *)rp;
    
    data = (uint32_t)*lp;
    data = ntohl(data);
    data = data &0xff0000;
    data=data>>16;   
    dprintf(INFO, "mipi_fl11280_read_id() data=0x%x\n",data);
     ret_data|=data;
    dprintf(INFO, "mipi_fl11280_read_id() ret_data=0x%x\n",ret_data);
    #endif
    return ret_data;
}

static char mipi_panel_ili6136s_page1[8] = {
0x04,0x00,0x29,0xc0,
0xFF,0x61,0x36,0x01
};
static char mipi_panel_ili6136s_readid[4] = {
  0x00, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili6136s_readid1[4] = {
  0x01, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili6136s_readid2[4] = {
  0x02, 0x00, 0x06, 0xa0}; /* DTYPE_DCS_READ */
static char mipi_panel_ili6136s_ack0[4] = {
  0x04, 0x00, 0x37, 0x80}; /* DTYPE_DCS_READ */
static struct mipi_dsi_cmd mipi_panel_ili6136s_change_page[] =
    {
	{sizeof(mipi_panel_ili6136s_page1),mipi_panel_ili6136s_page1}
    };

static struct mipi_dsi_cmd mipi_panel_ili6136s_read[] =
    {
	{sizeof(mipi_panel_ili6136s_readid),mipi_panel_ili6136s_readid}
    };
static struct mipi_dsi_cmd mipi_panel_ili6136s_read1[] =
    {
	{sizeof(mipi_panel_ili6136s_readid1),mipi_panel_ili6136s_readid1}
    };
static struct mipi_dsi_cmd mipi_panel_ili6136s_read2[] =
    {
	{sizeof(mipi_panel_ili6136s_readid2),mipi_panel_ili6136s_readid2}
    };
static struct mipi_dsi_cmd mipi_panel_ili6136s_cmda[] =
    {
	{sizeof(mipi_panel_ili6136s_ack0), mipi_panel_ili6136s_ack0}
    };
static uint32_t mipi_ili6136s_read_status(void)
{
    char rec_buf[24];
    char *rp = rec_buf;
    uint32_t *lp, data,ret_data;

	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_change_page, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_read1, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_cmda, 1);	
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_read, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_cmda, 1);	
    udelay(10);
	mipi_dsi_cmd_bta_sw_trigger();
    mipi_dsi_cmds_rx(&rp, 2);
    udelay(10);
	
    lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",data);
    data = data &0xff000000;
	dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",data);
	ret_data=data>>16;
	dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",ret_data);
	
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_read1, 1);
	mipi_dsi_cmds_tx(&mipi_panel_ili6136s_cmda, 1);	
    udelay(10);
	mipi_dsi_cmd_bta_sw_trigger();
    mipi_dsi_cmds_rx(&rp, 2);
    udelay(10);
	
    lp = (uint32_t *)rp;
    data = (uint32_t)*lp;
    data = ntohl(data);
    dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",data);
    data = data &0xff000000;
	dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",data);
	data=data>>24;
	dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",data);
	ret_data=ret_data|data;
	dprintf(INFO, "mipi_ili6136s_read_status() data=0x%x\n",ret_data);
    return ret_data;
}

#define LCD_ID 8

static int get_panel_id_state()
{
	uint8_t status = 0;

	gpio_tlmm_config(LCD_ID, 0, GPIO_INPUT, GPIO_PULL_UP, GPIO_2MA, GPIO_ENABLE);

	/* Get status of GPIO */
	status = gpio_status(LCD_ID);
	dprintf(SPEW, "get_panel_id_state = %d\n",status);

	return status;
}

/********************************************************************************
 ****detect which panel will be choose
 ********************************************************************************/
uint32_t panel_detect(uint32_t adc_min,uint32_t adc_max,uint32_t id,uint32_t ic_type,uint32_t lcd_adc)
{

    /*
    if ic name is 0, do not to read orise panel ic id
    if ic name is 1,read orise panel ic id
    if ic name is 2,read novatek nt35521 panel ic id   
    if ic name is 3,ilitek orise panel ic id
    if ic name is 4,ilitek himax panel ic id
	if ic name is 5,read novatek nt3559x panel ic id
	if ic name is 6,read rm68191 panel ic id
    */
	uint32_t  panel_ic_name;
	uint32_t lcd_val;
	
	lcd_val = get_lcd_adc();
	
	if((lcd_adc==1)&&(ic_type==0)){
		if((lcd_val>=adc_min)&&(lcd_val<=adc_max)){
			return 0xFFFF;
		}else{
              return 0xff;
		}	
	}else if((lcd_adc==0)&&(ic_type!=0)){
		if(1==ic_type){
        	panel_ic_name = mipi_xuyaokeji_otm_manufacture_id();
        }else if(2==ic_type){
        	panel_ic_name = mipi_novatek_id_read();
		}else if(3==ic_type){
        	panel_ic_name = mipi_ili9806e_read_status();		
		}else if(4==ic_type){
        	panel_ic_name = mipi_ili9806e_read_status();
		}else if(5==ic_type){
        	panel_ic_name = mipi_nt35596_id_read();
		}else if(6==ic_type){
        	panel_ic_name = mipi_rm68191_id_read();
		}else if(7==ic_type){
        	panel_ic_name = mipi_hx8379_read_id();
		}else if(8==ic_type){
		panel_ic_name = mipi_r61318_read_id();        	
		}else if(9==ic_type){
		panel_ic_name = mipi_rm68171_id_read(); 
		}else if(10==ic_type){
		panel_ic_name = mipi_hx8389b_read_id();
		#ifdef BOOT_FEATURE_A3001
		if(panel_ic_name==0x83&&1==get_panel_id_state())
		{
			panel_ic_name=0x8394D;
		}
		#endif 
		}else if(11==ic_type){
        	panel_ic_name = mipi_samsung_s6d7aa0x01_read_id(); 
		}else if(12==ic_type){
        	panel_ic_name = 0x51021; 
		}else if(13==ic_type){
        	panel_ic_name = 0x71410; 
		}else if(14==ic_type){
        	panel_ic_name = 0x71391; 
		}else if(15==ic_type){
					panel_ic_name = mipi_ili6136s_read_status(); 
		}else{
     		dprintf(INFO, "unknow  panel ic type\n");
			panel_ic_name = 0xff;
		}
	}else if ((lcd_adc==1)&&(ic_type!=0)){
		if((lcd_val<adc_min)||(lcd_val>adc_max))
		   return 0xff;
		if(1==ic_type){
        	panel_ic_name = mipi_xuyaokeji_otm_manufacture_id();
		}else if(2==ic_type){
        	panel_ic_name = mipi_novatek_id_read();
		}else if(3==ic_type){
        	panel_ic_name = mipi_ili9806e_read_status();	
		}else if(4==ic_type){
        	panel_ic_name = mipi_ili9806e_read_status();	
		}else if(5==ic_type){
        	panel_ic_name = mipi_nt35596_id_read();
		}else if(6==ic_type){
        	panel_ic_name = mipi_rm68191_id_read();
		}else if(7==ic_type){
        	panel_ic_name = mipi_hx8379_read_id();
		}else if(8==ic_type){
		 panel_ic_name = mipi_r61318_read_id();        	
		}else if(9==ic_type){
		panel_ic_name = mipi_rm68171_id_read(); 
		}else if(10==ic_type){
		panel_ic_name = mipi_fl11280_read_id(); 
		}else{
     		dprintf(INFO, "unknow  panel ic type\n");
			panel_ic_name = 0xff;
		}
	}
	return panel_ic_name;
}

