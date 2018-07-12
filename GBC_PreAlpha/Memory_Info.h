#pragma once

// Memory - Offset
const unsigned short ROM_B0_OFFSET	 = 0x0000;  
const unsigned short ROM_Bn_OFFSET	 = 0x4000;
const unsigned short CRAM_OFFSET	 = 0x8000;
const unsigned short BGD1_OFFSET	 = 0x9800;
const unsigned short BGD2_OFFSET	 = 0x9C00;
const unsigned short ERAM_OFFSET	 = 0xA000;
const unsigned short IROM_B0_OFFSET	 = 0xC000;
const unsigned short IROM_Bn_OFFSET	 = 0xD000;
const unsigned short ECHO_RAM_OFFSET = 0xE000;
const unsigned short OAM_OFFSET		 = 0xFE00;
const unsigned short UUM_OFFSET		 = 0xFEA0;
const unsigned short IOREG_OFFSET	 = 0xFF00;
const unsigned short ZP_OFFSET		 = 0xFF80;

// Memory - Size
const unsigned short ROM_B0_SIZE	 = 0x4000;
const unsigned short ROM_Bn_SIZE	 = 0x4000;
const unsigned short CRAM_SIZE		 = 0x1800;
const unsigned short BGD1_SIZE		 = 0x0400;
const unsigned short BGD2_SIZE		 = 0x0400;
const unsigned short ERAM_SIZE		 = 0x2000;
const unsigned short IRAM_B0_SIZE	 = 0x1000;
const unsigned short IRAM_Bn_SIZE	 = 0x1000;
const unsigned short ECHO_RAM_SIZE   = 0x1E00;
const unsigned short OAM_SIZE		 = 0x00A0;
const unsigned short UUM_SIZE		 = 0x0060;
const unsigned short IOREG_SIZE		 = 0x0080;
const unsigned short ZP_SIZE		 = 0x0080;

