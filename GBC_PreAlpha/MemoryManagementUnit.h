#pragma once
#include <iostream>
#include <vector>

#include "Cartridge_Info.h"

class MemoryManagementUnit
{
private:
	Cartridge_Info cartInfo;

	bool runningBootCode = true;
	unsigned char *BP = nullptr;

	//////////////Memory Banks/////////////////////
	unsigned char selected_ROM_bank  = 0;
	unsigned char selected_EROM_bank = 0;
	unsigned char selected_IROM_bank = 0;

	unsigned char ROM_banks  = 0;
	unsigned char EROM_banks = 0;
	unsigned char IROM_banks = 8;

	//////////////Memory Base Pointers//////////////
	unsigned char* baseROM_0 = nullptr;
	std::vector<unsigned char*> baseROM_n;
	std::vector<unsigned char*> baseCRAM;
	std::vector<unsigned char*> baseBGD1;
	std::vector<unsigned char*> baseBGD2;
	std::vector<unsigned char*> baseERAM_n;
	unsigned char* baseIRAM_0 = nullptr;
	std::vector<unsigned char*> baseIRAM_n;
	unsigned char* baseEchoRAM = nullptr;
	unsigned char* baseOAM = nullptr;
	unsigned char* baseUUM = nullptr;
	unsigned char* baseIOREG = nullptr;
	unsigned char* baseZP = nullptr;

	///////////////IO Register Pointers//////////////
	unsigned char* P1_ptr   = nullptr;
	unsigned char* SB_ptr   = nullptr;
	unsigned char* SC_ptr   = nullptr;
	unsigned char* DIV_ptr  = nullptr;
	unsigned char* TIMA_ptr = nullptr;
	unsigned char* TMA_ptr  = nullptr;
	unsigned char* TAC_ptr  = nullptr;
	unsigned char* IF_ptr   = nullptr;
	unsigned char* IE_ptr   = nullptr;
	unsigned char* LCDC_ptr = nullptr;
	unsigned char* STAT_ptr = nullptr;
	unsigned char* SCY_ptr  = nullptr;
	unsigned char* SCX_ptr  = nullptr;
	unsigned char* LY_ptr   = nullptr;
	unsigned char* LYC_ptr  = nullptr;
	unsigned char* BCPS_ptr = nullptr;
	unsigned char* BCPD_ptr = nullptr;
	unsigned char* OCPS_ptr = nullptr;
	unsigned char* OCPD_ptr = nullptr;
	unsigned char* WY_ptr   = nullptr;
	unsigned char* WX_ptr   = nullptr;

public:
	void initMMU(char * cartridgeBase);

	void write(unsigned short address, unsigned char value);
	unsigned char read(unsigned short address);

	MemoryManagementUnit();
	~MemoryManagementUnit();
};

