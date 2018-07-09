#include "MemoryManagementUnit.h"
#include "Memory_Info.h"

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

	BP = new unsigned char[memorySize];

	baseROM_0 = BP;
	for (unsigned char count = 0; count < ROM_banks; count++)
	{
		baseROM_n.push_back(baseROM_0 + ROM_B0_SIZE + (ROM_Bn_SIZE * count));
	}
	baseCRAM.push_back(baseROM_n.back() + ROM_Bn_SIZE);
	baseCRAM.push_back(baseROM_n.back() + ROM_Bn_SIZE + CRAM_SIZE);
	baseBGD1.push_back(baseCRAM.back() + CRAM_SIZE);
	baseBGD1.push_back(baseCRAM.back() + CRAM_SIZE + BGD1_SIZE);
	baseBGD2.push_back(baseBGD1.back() + BGD1_SIZE);
	baseBGD2.push_back(baseBGD1.back() + BGD1_SIZE + BGD2_SIZE);
	for (unsigned char count = 0; count < EROM_banks; count++)
	{
		baseERAM_n.push_back(baseBGD2.back() + BGD2_SIZE + (ERAM_SIZE * count));
	}
	baseIRAM_0 = baseERAM_n.back() + ERAM_SIZE;
	for (unsigned char count = 0; count < 8; count++)
	{
		baseIRAM_n.push_back(baseIRAM_0 + IRAM_B0_SIZE + (IRAM_Bn_SIZE * count));
	}
	baseEchoRAM = baseIRAM_n.back() + IRAM_Bn_SIZE;
	baseOAM = baseEchoRAM + ECHO_RAM_SIZE;
	baseUUM = baseOAM + OAM_SIZE;
	baseIOREG = baseUUM + UUM_SIZE;
	baseZP = baseIOREG + IOREG_SIZE;
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
	unsigned char value;

	if (address < ROM_Bn_OFFSET)
	{
		if ((runningBootCode == true) && (address <= 0xff))
		{
			BootROM[address];
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
