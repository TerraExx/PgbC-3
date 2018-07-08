#pragma once
#include "Cartridge_Info.h"

class MemoryManagementUnit
{
private:
	Cartridge_Info cartInfo;

	bool runningBootCode = true;
	unsigned char *BP = nullptr;

	unsigned char selected_ROM_bank  = 0;
	unsigned char selected_EROM_bank = 0;
	unsigned char selected_IROM_bank = 0;

	unsigned char ROM_banks  = 0;
	unsigned char EROM_banks = 0;
	unsigned char IROM_banks = 8;

public:
	void initMMU(char * cartridgeBase);

	void write(unsigned short address, unsigned char value);

	unsigned char read(unsigned short address);

	MemoryManagementUnit();
	~MemoryManagementUnit();
};

