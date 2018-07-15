#include <cstring>

#include "MemoryManagementUnit.h"
#include "Memory_Info.h"
#include "Reg_Info.h"

unsigned char BootROM[] = 
{
	0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
	0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
	0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
	0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
	0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
	0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
	0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
	0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
	0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
	0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
	0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
	0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
	0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
	0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
	0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
	0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50 
};

void MemoryManagementUnit::initMMU(char * cartridgeBase)
{
	unsigned int memorySize = 0;

	////////////////////Read ROM Header//////////////////////
	cartInfo.initCartridgeInfo(cartridgeBase);

	switch (cartInfo.ROMsize)
	{
	case S_32_KB_2_banks:	ROM_banks = 2;   break;
	case S_64_KB_4_banks:	ROM_banks = 4;   break;
	case S_128_KB_8_banks:	ROM_banks = 8;   break;
	case S_256_KB_16_banks: ROM_banks = 16;  break;
	case S_512_KB_32_banks: ROM_banks = 32;  break;
	case S_1_MB_64_banks:	ROM_banks = 64;  break;
	case S_2_MB_128_banks:	ROM_banks = 128; break;
	case S_1_1_MB_72_banks: ROM_banks = 72;  break;
	case S_1_2_MB_80_banks: ROM_banks = 80;  break;
	case S_1_5_MB_96_banks: ROM_banks = 96;  break;
	default: break;
	}

	switch (cartInfo.ERAMsize)
	{
	case None:				EROM_banks = 0;	 break;
	case S_2_KB_1_banks:	EROM_banks = 1;	 break;
	case S_8_KB_1_banks:	EROM_banks = 1;	 break;
	case S_32_KB_4_banks:	EROM_banks = 4;	 break;
	case S_128_KB_16_banks:	EROM_banks = 16; break;
	}

	////////////////////Calculate Req. Memory//////////////////////
	memorySize += ROM_Bn_SIZE * ROM_banks;
	memorySize += CRAM_SIZE * 2;
	memorySize += BGD1_SIZE * 2;
	memorySize += BGD2_SIZE * 2;
	memorySize += ERAM_SIZE * EROM_banks;
	memorySize += IRAM_B0_SIZE * 8;
	memorySize += ECHO_RAM_SIZE;
	memorySize += OAM_SIZE;
	memorySize += UUM_SIZE;
	memorySize += IOREG_SIZE;
	memorySize += ZP_SIZE;

	////////////////////Set Base Pointers//////////////////////
	BP          = new unsigned char[memorySize];
	baseROM_0   = BP;
	for (unsigned char count = 0; count < (ROM_banks - 1); count++)
	{
		baseROM_n.push_back(baseROM_0 + ROM_B0_SIZE + (ROM_Bn_SIZE * count));
	}
	baseCRAM.push_back(baseROM_n.back() + ROM_Bn_SIZE );
	baseCRAM.push_back(baseROM_n.back() + ROM_Bn_SIZE + CRAM_SIZE);
	baseBGD1.push_back(baseCRAM.back()  + CRAM_SIZE   );
	baseBGD1.push_back(baseCRAM.back()  + CRAM_SIZE   + BGD1_SIZE);
	baseBGD2.push_back(baseBGD1.back()  + BGD1_SIZE   );
	baseBGD2.push_back(baseBGD1.back()  + BGD1_SIZE   + BGD2_SIZE);
	for (unsigned char count = 0; count < EROM_banks; count++)
	{
		baseERAM_n.push_back(baseBGD2.back() + BGD2_SIZE + (ERAM_SIZE * count));
	}
	baseIRAM_0  = baseERAM_n.back() + ERAM_SIZE;
	for (unsigned char count = 0; count < 7; count++)
	{
		baseIRAM_n.push_back(baseIRAM_0 + IRAM_B0_SIZE + (IRAM_Bn_SIZE * count));
	}
	baseEchoRAM = baseIRAM_n.back() + IRAM_Bn_SIZE;
	baseOAM     = baseEchoRAM		+ ECHO_RAM_SIZE;
	baseUUM     = baseOAM			+ OAM_SIZE;
	baseIOREG   = baseUUM			+ UUM_SIZE;
	baseZP      = baseIOREG			+ IOREG_SIZE;

	////////////////////Copy Cartridge ROM//////////////////////
	std::memcpy(baseROM_0, cartridgeBase, ROM_Bn_SIZE*ROM_banks);

	////////////////////Init Registers//////////////////////
	auto getOffset = [](unsigned char mask) -> unsigned char
	{
		unsigned char ret = 0;

		while (!(mask & 0x01))
		{
			mask = mask >> 1;
			++ret;
		}

		return ret;
	};

	auto getHash = [](const unsigned char& reg, const unsigned char& mask) -> unsigned short
	{
		return (reg << 8) | mask;
	};

	offsetHash.insert({ getHash(P1, P1_P10_IN) , getOffset(P1_P10_IN) });
	offsetHash.insert({ getHash(P1, P1_P11_IN) , getOffset(P1_P11_IN) });
	offsetHash.insert({ getHash(P1, P1_P12_IN) , getOffset(P1_P12_IN) });
	offsetHash.insert({ getHash(P1, P1_P13_IN) , getOffset(P1_P13_IN) });
	offsetHash.insert({ getHash(P1, P1_P14_OUT) , getOffset(P1_P14_OUT) });
	offsetHash.insert({ getHash(P1, P1_P15_OUT) , getOffset(P1_P15_OUT) });

	offsetHash.insert({ getHash(SC, SC_TRANSFER_START) , getOffset(SC_TRANSFER_START) });
	offsetHash.insert({ getHash(SC, SC_CLOCK_SPEED) , getOffset(SC_CLOCK_SPEED) });
	offsetHash.insert({ getHash(SC, SC_SHIFT_CLOCK) , getOffset(SC_SHIFT_CLOCK) });

	offsetHash.insert({ getHash(TAC, TAC_INPUT_CLOCK) , getOffset(TAC_INPUT_CLOCK) });
	offsetHash.insert({ getHash(TAC, TAC_TIMER_START) , getOffset(TAC_TIMER_START) });

	offsetHash.insert({ getHash(IF, IF_VB) , getOffset(IF_VB) });
	offsetHash.insert({ getHash(IF, IF_LCDC) , getOffset(IF_LCDC) });
	offsetHash.insert({ getHash(IF, IF_TO) , getOffset(IF_TO) });
	offsetHash.insert({ getHash(IF, IF_SIO) , getOffset(IF_SIO) });
	offsetHash.insert({ getHash(IF, IF_P1) , getOffset(IF_P1) });

	offsetHash.insert({ getHash(IE, IE_VB) , getOffset(IE_VB) });
	offsetHash.insert({ getHash(IE, IE_LCDC) , getOffset(IE_LCDC) });
	offsetHash.insert({ getHash(IE, IE_TO) , getOffset(IE_TO) });
	offsetHash.insert({ getHash(IE, IE_SIO) , getOffset(IE_SIO) });
	offsetHash.insert({ getHash(IE, IE_P1) , getOffset(IE_P1) });

	offsetHash.insert({ getHash(LCDC, LCDC_BG_DISPLAY_STATE) , getOffset(LCDC_BG_DISPLAY_STATE) });
	offsetHash.insert({ getHash(LCDC, LCDC_OBJ_ON) , getOffset(LCDC_OBJ_ON) });
	offsetHash.insert({ getHash(LCDC, LCDC_OBJ_BLOCK_COMPOSITION) , getOffset(LCDC_OBJ_BLOCK_COMPOSITION) });
	offsetHash.insert({ getHash(LCDC, LCDC_BG_CODE_AREA) , getOffset(LCDC_BG_CODE_AREA) });
	offsetHash.insert({ getHash(LCDC, LCDC_BG_CHARACTER_DATA) , getOffset(LCDC_BG_CHARACTER_DATA) });
	offsetHash.insert({ getHash(LCDC, LCDC_WINDOW_ON) , getOffset(LCDC_WINDOW_ON) });
	offsetHash.insert({ getHash(LCDC, LCDC_WINDOW_CODE_AREA) , getOffset(LCDC_WINDOW_CODE_AREA) });
	offsetHash.insert({ getHash(LCDC, LCDC_OPERATION_STOP) , getOffset(LCDC_OPERATION_STOP) });
	
	offsetHash.insert({ getHash(STAT, STAT_MODE_FLAG) , getOffset(STAT_MODE_FLAG) });
	offsetHash.insert({ getHash(STAT, STAT_MATCH_FLAG) , getOffset(STAT_MATCH_FLAG) });
	offsetHash.insert({ getHash(STAT, STAT_IR_MODE_00) , getOffset(STAT_IR_MODE_00) });
	offsetHash.insert({ getHash(STAT, STAT_IR_MODE_01) , getOffset(STAT_IR_MODE_01) });
	offsetHash.insert({ getHash(STAT, STAT_IR_MODE_10) , getOffset(STAT_IR_MODE_10) });
	offsetHash.insert({ getHash(STAT, STAT_LYC) , getOffset(STAT_LYC) });
	
	offsetHash.insert({ getHash(BGP, BGP_00) , getOffset(BGP_00) });
	offsetHash.insert({ getHash(BGP, BGP_01) , getOffset(BGP_01) });
	offsetHash.insert({ getHash(BGP, BGP_10) , getOffset(BGP_10) });
	offsetHash.insert({ getHash(BGP, BGP_11) , getOffset(BGP_11) });
	
	offsetHash.insert({ getHash(OBP0, OBP0_00) , getOffset(OBP0_00) });
	offsetHash.insert({ getHash(OBP0, OBP0_01) , getOffset(OBP0_01) });
	offsetHash.insert({ getHash(OBP0, OBP0_10) , getOffset(OBP0_10) });
	offsetHash.insert({ getHash(OBP0, OBP0_11) , getOffset(OBP0_11) });
	
	offsetHash.insert({ getHash(BCPS, BCPS_HL) , getOffset(BCPS_HL) });
	offsetHash.insert({ getHash(BCPS, BCPS_PALLET_DATA_NUM) , getOffset(BCPS_PALLET_DATA_NUM) });
	offsetHash.insert({ getHash(BCPS, BCPS_PALLET_NUM) , getOffset(BCPS_PALLET_NUM) });
	offsetHash.insert({ getHash(BCPS, BCPS_FLAG) , getOffset(BCPS_FLAG) });
	
	offsetHash.insert({ getHash(OCPS, OCPS_HL) , getOffset(OCPS_HL) });
	offsetHash.insert({ getHash(OCPS, OCPS_PALLET_DATA_NUM) , getOffset(OCPS_PALLET_DATA_NUM) });
	offsetHash.insert({ getHash(OCPS, OCPS_PALLET_NUM) , getOffset(OCPS_PALLET_NUM) });
	offsetHash.insert({ getHash(OCPS, OCPS_FLAG) , getOffset(OCPS_FLAG) });
	
	offsetHash.insert({ getHash(KEY1, KEY1_ESS) , getOffset(KEY1_ESS) });
	offsetHash.insert({ getHash(KEY1, KEY1_CS) , getOffset(KEY1_CS) });
	
	offsetHash.insert({ getHash(VBK, VBK_BANK) , getOffset(VBK_BANK) });
	
	offsetHash.insert({ getHash(SVBK, SVBK_BANK) , getOffset(SVBK_BANK) });
}

void MemoryManagementUnit::write(unsigned short address, unsigned char value)
{
	if (address < ROM_Bn_OFFSET)
	{
		// TODO Implement MBC
	}
	else if (address < CRAM_OFFSET)
	{
		// TODO Implement MBC
	}
	else if (address < BGD1_OFFSET)
	{
		baseCRAM.at(0)[address - CRAM_OFFSET] = value;

		// ReDraw Tile
		VRAM_D.draw((address - CRAM_OFFSET) / 0x10
				   , baseCRAM[0] + 0x10 * ((address - CRAM_OFFSET) / 0x10)
			       , getReg(BGP)
		           );
	}
	else if (address < BGD2_OFFSET)
	{
		baseBGD1.at(0)[address - BGD1_OFFSET] = value;
	}
	else if (address < ERAM_OFFSET)
	{
		baseBGD2.at(0)[address - BGD2_OFFSET] = value;
	}
	else if (address < IROM_B0_OFFSET)
	{
		baseERAM_n.at(selected_EROM_bank)[address - ERAM_OFFSET] = value;
	}
	else if (address < IROM_Bn_OFFSET)
	{
		baseIRAM_0[address - IROM_B0_OFFSET] = value;
	}
	else if (address < ECHO_RAM_OFFSET)
	{
		baseIRAM_n.at(IROM_banks)[address - IROM_Bn_OFFSET] = value;
	}
	else if (address < OAM_OFFSET)
	{
		baseEchoRAM[address - ECHO_RAM_OFFSET] = value;
	}
	else if (address < UUM_OFFSET)
	{
		baseOAM[address - OAM_OFFSET] = value;
	}
	else if (address < IOREG_OFFSET)
	{
		std::cout << "Writing to unusable memory\n";
		exit(1);
	}
	else if (address < ZP_OFFSET)
	{
		baseIOREG[address - IOREG_OFFSET] = value;
	}
	else
	{
		baseZP[address - ZP_OFFSET] = value;
	}
}

unsigned char MemoryManagementUnit::read(unsigned short address)
{
	unsigned char value = 0x00;

	if (address < ROM_Bn_OFFSET)
	{
		if ((runningBootCode == true) && (address <= 0x00ff))
		{
			value = BootROM[address];
		}
		else
		{
			value = baseROM_0[address];
		}
	}
	else if (address < CRAM_OFFSET)
	{
		value = baseROM_n.at(ROM_banks)[address - ROM_Bn_OFFSET];
	}
	else if (address < BGD1_OFFSET)
	{
		value = baseCRAM.at(0)[address - CRAM_OFFSET];
	}
	else if (address < BGD2_OFFSET)
	{
		value = baseBGD1.at(0)[address - BGD1_OFFSET];
	}
	else if (address < ERAM_OFFSET)
	{
		value = baseBGD2.at(0)[address - BGD2_OFFSET];
	}
	else if (address < IROM_B0_OFFSET)
	{
		value = baseERAM_n.at(selected_EROM_bank)[address - ERAM_OFFSET];
	}
	else if (address < IROM_Bn_OFFSET)
	{
		value = baseIRAM_0[address - IROM_B0_OFFSET];
	}
	else if (address < ECHO_RAM_OFFSET)
	{
		value = baseIRAM_n.at(IROM_banks)[address - IROM_Bn_OFFSET];
	}
	else if (address < OAM_OFFSET)
	{
		value = baseEchoRAM[address - ECHO_RAM_OFFSET];
	}
	else if (address < UUM_OFFSET)
	{
		value = baseOAM[address - OAM_OFFSET];
	}
	else if (address < IOREG_OFFSET)
	{
		std::cout << "Reading from unusable memory\n";
		exit(1);
	}
	else if (address < ZP_OFFSET)
	{
		value = baseIOREG[address - IOREG_OFFSET];
	}
	else
	{
		value = baseZP[address - ZP_OFFSET];
	}

	return value;
}

unsigned char MemoryManagementUnit::getReg(const unsigned short& reg, const unsigned char& bit)
{
	unsigned char value = read(reg);
	unsigned char mask = bit;

	if (bit != 0xff)
	{
		value = value & bit;

		while (!(mask & 0x01))
		{
			mask = mask >> 1;
			value = value >> 1;
		}
	}

	return value;
}

MemoryManagementUnit::MemoryManagementUnit()
{
}


MemoryManagementUnit::~MemoryManagementUnit()
{
	if (BP != nullptr)
	{
		delete[] BP;
	}
}
