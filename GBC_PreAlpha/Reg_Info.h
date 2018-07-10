#pragma once
/*
	\name		P1
	\info		Register for reading joy pad info and determining type

	\address	0xFF00
	\type		R/W
*/
const unsigned char P1 = 0x00;

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
const unsigned char SB = 0x01;

/*
	\name		SC
	\info		SIO control

	\address	0xFF02
	\type		R/W
*/
const unsigned char SC = 0x02;

const unsigned char SB_TRANSFER_START = 0x1;
const unsigned char SB_CLOCK_SPEED    = 0x2;
const unsigned char SB_SHIFT_CLOCK    = 0x8;

/*
	\name		DIV
	\info		Divider Register. Writing to this register set's it to 0.

	\address	0xFF04
	\type		R/W
*/
const unsigned char DIV = 0x04;

/*
	\name		TIMA
	\info		Timer counter that operates using the TAC clock.
				

	\address	0xFF05
	\type		R/W
*/
const unsigned char TIMA = 0x05;

/*
	\name		TMA
	\info		Timer Modulo. TIMA is set to TMA on overflow.

	\address	0xFF06
	\type		R/W
*/
const unsigned char TMA = 0x06;

/*
	\name		TAC
	\info		Timer Control. Starts/Stops the timer. Sets the feq.

	\address	0xFF07
	\type		R/W
*/
const unsigned char TAC = 0x7;

const unsigned char TAC_INPUT_CLOCK = 0x03;
const unsigned char TAC_TIMER_START = 0x04;

/*
	\name		IF
	\info		Interrupt Req. Flag Register. 

	\address	0xFF0F
\	type		R/W
*/
const unsigned char IF = 0x0F;

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
const unsigned char IE = 0xFF;

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
const unsigned char LCDC = 0x40;

const unsigned char LCDC_BG_DISPLAY_STATE		= 0x01;
const unsigned char LCDC_OBJ_ON					= 0x02;
const unsigned char LCDC_OBJ_BLOCK_COMPOSITION	= 0x04;
const unsigned char LCDC_BG_CODE_AREA			= 0x08;
const unsigned char LCDC_BG_CHARACTER_DATA		= 0x10;
const unsigned char LCDC_WINDOW_ON				= 0x20;
const unsigned char LCDC_WINDOW_CODE_AREA		= 0x40;
const unsigned char LCDC_OPERATION_STOP			= 0x80;

/*
	\name		STAT
	\info		LCDC Status Flag Register.

	\address	0xFF41
	\type		R/W
*/
const unsigned char STAT = 0x41;

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
const unsigned char SCY = 0x42;

/*
	\name		SCX
	\info		Scroll X

	\address	0xFF43
	\type		R/W
*/
const unsigned char SCX = 0x43;

/*
	\name		LY
	\info		LCDC y-cordinate

	\address	0xFF44
	\type		R/W
*/
const unsigned char LY = 0x44;

/*
	\name		LYC
	\info		LY compare

	\address	0xFF45
	\type		R/W
*/
const unsigned char LYC = 0x45;

/*
	\name		BCPS
	\info		Specifies a BG write

	\address	0xFF68
	\type		R/W
*/
const unsigned char BCPS = 0x68;

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
const unsigned char BCPD = 0x69;

/*
	\name		OCPS
	\info		Specifies a OBJ write

	\address	0xFF6A
	\type		R/W
*/
const unsigned char OCPS = 0x6A;

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
const unsigned char OCPD = 0x6B;

/*
	\name		WY
	\info		Windows y-coordinate

	\address	0xFF4A
	\type		R/W
*/
const unsigned char WY = 0x4A;

/*
	\name		WX
	\info		Windows x-coordinate

	\address	0xFF4B
	\type		R/W
*/
const unsigned char WX = 0x4B;
