#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>

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
	unsigned char* baseROM_0   = nullptr;
	std::vector<unsigned char*>  baseROM_n;
	std::vector<unsigned char*>  baseCRAM;
	std::vector<unsigned char*>  baseBGD1;
	std::vector<unsigned char*>  baseBGD2;
	std::vector<unsigned char*>  baseERAM_n;
	unsigned char* baseIRAM_0  = nullptr;
	std::vector<unsigned char*>  baseIRAM_n;
	unsigned char* baseEchoRAM = nullptr;
	unsigned char* baseOAM     = nullptr;
	unsigned char* baseUUM     = nullptr;
	unsigned char* baseIOREG   = nullptr;
	unsigned char* baseZP      = nullptr;

	///////////////IO Register Offests//////////////
	std::unordered_map<unsigned short, unsigned char> offsetHash;

public:
	void initMMU(char * cartridgeBase);

	void write(unsigned short address, unsigned char value);
	unsigned char read(unsigned short address);

	unsigned char getReg(const unsigned char& reg, const unsigned char& bit = 0xFF);

	MemoryManagementUnit();
	~MemoryManagementUnit();
};

