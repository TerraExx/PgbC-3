#pragma once
/*
	\name		P1
	\info		Register for reading joy pad info and determining type

	\address	0xFF00
	\type		R/W
*/
const unsigned short P1 = 0xFF00;

const unsigned char P1_P10_IN  = 0x01;
const unsigned char P1_P11_IN  = 0x02;
const unsigned char P1_P12_IN  = 0x04;
const unsigned char P1_P13_IN  = 0x08;
const unsigned char P1_P14_OUT = 0x10;
const unsigned char P1_P15_OUT = 0x20;

/*
	\name		SB
	\info		Serial transfer data.
				8 bits to be read/written.

	\address	0xFF01
	\type		R/W
*/
const unsigned short SB = 0xFF01;

/*
	\name		SC
	\info		SIO control

	\address	0xFF02
	\type		R/W
*/
const unsigned short SC = 0xFF02;

const unsigned char SC_TRANSFER_START = 0x1;
const unsigned char SC_CLOCK_SPEED    = 0x2;
const unsigned char SC_SHIFT_CLOCK    = 0x8;

/*
	\name		DIV
	\info		Divider Register. Writing to this register set's it to 0.

	\address	0xFF04
	\type		R/W
*/
const unsigned short DIV = 0xFF04;

/*
	\name		TIMA
	\info		Timer counter that operates using the TAC clock.
				

	\address	0xFF05
	\type		R/W
*/
const unsigned short TIMA = 0xFF05;

/*
	\name		TMA
	\info		Timer Modulo. TIMA is set to TMA on overflow.

	\address	0xFF06
	\type		R/W
*/
const unsigned short TMA = 0xFF06;

/*
	\name		TAC
	\info		Timer Control. Starts/Stops the timer. Sets the feq.

	\address	0xFF07
	\type		R/W
*/
const unsigned short TAC = 0xFF07;

const unsigned char TAC_INPUT_CLOCK = 0x03;
const unsigned char TAC_TIMER_START = 0x04;

/*
	\name		IF
	\info		Interrupt Req. Flag Register. 

	\address	0xFF0F
\	type		R/W
*/
const unsigned short IF = 0xFF0F;

const unsigned char IF_VB   = 0x01;
const unsigned char IF_LCDC = 0x02;
const unsigned char IF_TO   = 0x04;
const unsigned char IF_SIO  = 0x08;
const unsigned char IF_P1   = 0x10;

/*
	\name		IE
	\info		Interrupt Enable.

	\address	0xFFFF
	\type		R/W
*/
const unsigned short IE = 0xFFFF;

const unsigned char IE_VB   = 0x01;
const unsigned char IE_LCDC = 0x02;
const unsigned char IE_TO   = 0x04;
const unsigned char IE_SIO  = 0x08;
const unsigned char IE_P1   = 0x10;

/*
	\name		LCDC
	\info		LCD Control Register.

	\address	0xFF40
	\type		R/W
*/
const unsigned short LCDC = 0xFF40;

const unsigned char LCDC_BG_PRIORITY		    = 0x01;
const unsigned char LCDC_OBJ_ON					= 0x02;
const unsigned char LCDC_OBJ_BLOCK_COMPOSITION	= 0x04;
const unsigned char LCDC_BG_CODE_AREA			= 0x08;
const unsigned char LCDC_BG_CHARACTER_DATA		= 0x10;
const unsigned char LCDC_WINDOW_ON				= 0x20;
const unsigned char LCDC_WINDOW_CODE_AREA		= 0x40;
const unsigned char LCDC_DISPLAY_ENABLE			= 0x80;

/*
	\name		STAT
	\info		LCDC Status Flag Register.

	\address	0xFF41
	\type		R/W
*/
const unsigned short STAT = 0xFF41;

const unsigned char STAT_MODE_FLAG  = 0x03;
const unsigned char STAT_MATCH_FLAG = 0x04;
const unsigned char STAT_IR_MODE_00 = 0x08;
const unsigned char STAT_IR_MODE_01 = 0x10;
const unsigned char STAT_IR_MODE_10 = 0x20;
const unsigned char STAT_LYC        = 0x40;

/*
	\name		SCY
	\info		Scroll Y

	\address	0xFF42
	\type		R/W
*/
const unsigned short SCY = 0xFF42;

/*
	\name		SCX
	\info		Scroll X

	\address	0xFF43
	\type		R/W
*/
const unsigned short SCX = 0xFF43;

/*
	\name		LY
	\info		LCDC y-cordinate

	\address	0xFF44
	\type		R
*/
const unsigned short LY = 0xFF44;

/*
	\name		LYC
	\info		LY compare

	\address	0xFF45
	\type		R/W
*/
const unsigned short LYC = 0xFF45;

/*
	\name		DMA
	\info		DMA transfer starts as soon as the address is set

	\address	0xFF46
	\type		W
*/
const unsigned short DMA = 0xFF46;

/*
	\name		BGP
	\info		Background pallet data

	\address	0xFF47
	\type		W
*/
const unsigned short BGP = 0xFF47;

const unsigned char BGP_00 = 0x03;
const unsigned char BGP_01 = 0x0C;
const unsigned char BGP_10 = 0x30;
const unsigned char BGP_11 = 0xC0;

/*
	\name		OBP0
	\info		Object pallet data 0

	\address	0xFF48
	\type		W
*/
const unsigned short OBP0 = 0xFF48;

const unsigned char OBP0_00 = 0x03;
const unsigned char OBP0_01 = 0x0C;
const unsigned char OBP0_10 = 0x30;
const unsigned char OBP0_11 = 0xC0;

/*
\name		OBP1
\info		Object pallet data 1

\address	0xFF49
\type		W
*/
const unsigned short OBP1 = 0xFF49;

const unsigned char OBP1_00 = 0x03;
const unsigned char OBP1_01 = 0x0C;
const unsigned char OBP1_10 = 0x30;
const unsigned char OBP1_11 = 0xC0;

/*
	\name		BCPS
	\info		Specifies a BG write

	\address	0xFF68
	\type		R/W
*/
const unsigned short BCPS = 0xFF68;

const unsigned char BCPS_HL				 = 0x01;
const unsigned char BCPS_PALLET_DATA_NUM = 0x06;
const unsigned char BCPS_PALLET_NUM		 = 0x38;
const unsigned char BCPS_FLAG			 = 0x80;

/*
	\name		BCPD
	\info		Specifies a BG write data

	\address	0xFF69
	\type		R/W
*/
const unsigned short BCPD = 0xFF69;

/*
	\name		OCPS
	\info		Specifies a OBJ write

	\address	0xFF6A
	\type		R/W
*/
const unsigned short OCPS = 0xFF6A;

const unsigned char OCPS_HL              = 0x01;
const unsigned char OCPS_PALLET_DATA_NUM = 0x06;
const unsigned char OCPS_PALLET_NUM      = 0x38;
const unsigned char OCPS_FLAG            = 0x80;

/*
	\name		OCPD
	\info		Specifies a OBJ write data

	\address	0xFF6B
	\type		R/W
*/
const unsigned short OCPD = 0xFF6B;

/*
	\name		WY
	\info		Windows y-coordinate

	\address	0xFF4A
	\type		R/W
*/
const unsigned short WY = 0xFF4A;

/*
	\name		WX
	\info		Windows x-coordinate

	\address	0xFF4B
	\type		R/W
*/
const unsigned short WX = 0xFF4B;

/*
	\name		KEY1
	\info		Speed switching register

	\address	0xFF4D
	\type		R/W
*/
const unsigned short KEY1 = 0xFF4D;

const unsigned char KEY1_ESS = 0x01;
const unsigned char KEY1_CS  = 0x80;

/*
	\name		VBK
	\info		VRAM bank select register

	\address	0xFF4F
	\type		R/W
*/
const unsigned short VBK = 0xFF4F;

const unsigned char VBK_BANK = 0x01;

/*
	\name		SVBK
	\info		WRAM bank select register

	\address	0xFF70
	\type		R/W
*/
const unsigned short SVBK = 0xFF70;

const unsigned char SVBK_BANK = 0x07;
