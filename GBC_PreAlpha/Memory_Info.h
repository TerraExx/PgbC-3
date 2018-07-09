#pragma once

// Memory - Offset
const short ROM_B0_OFFSET	= 0x0000;  
const short ROM_Bn_OFFSET	= 0X4000;
const short CRAM_OFFSET		= 0X8000;
const short BGD1_OFFSET		= 0X9800;
const short BGD2_OFFSET		= 0X9C00;
const short ERAM_OFFSET		= 0XA000;
const short IROM_B0_OFFSET	= 0XC000;
const short IROM_Bn_OFFSET	= 0XD000;
const short ECHO_RAM_OFFSET	= 0XE000;
const short OAM_OFFSET		= 0XFE00;
const short UUM_OFFSET		= 0XFEA0;
const short IOREG_OFFSET	= 0xFF00;
const short ZP_OFFSET		= 0XFF80;

// Memory - Size
const short ROM_B0_SIZE		= 0x4000;
const short ROM_Bn_SIZE		= 0x4000;
const short CRAM_SIZE		= 0X1800;
const short BGD1_SIZE		= 0X0400;
const short BGD2_SIZE		= 0X0400;
const short ERAM_SIZE		= 0X2000;
const short IRAM_B0_SIZE	= 0X1000;
const short IRAM_Bn_SIZE	= 0X1000;
const short ECHO_RAM_SIZE   = 0X1E00;
const short OAM_SIZE		= 0X00A0;
const short UUM_SIZE		= 0X0060;
const short IOREG_SIZE		= 0x0080;
const short ZP_SIZE			= 0X0080;

