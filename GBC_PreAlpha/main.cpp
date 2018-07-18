#include <fstream>
#include <iostream>

#include "Cartridge_Info.h"
#include "CentralProcessingUnit.h"
#include "PixelProcessingUnit.h"

bool DEBUG_PRINTOUT = false;

int main(int argc, char* argv[]) {
	MemoryManagementUnit MMU;
	CentralProcessingUnit CPU(MMU);
	PixelProcessingUnit PPU(MMU, CPU);

	char *cartridgeBase;

	std::ifstream file("C:\\ROMs\\Tetris DX (World).gbc", std::ios::in | std::ios::binary | std::ios::ate);

	if (file.is_open() == false)
	{
		std::cout << "Unable to open file\n";
		exit(1);
	}

	unsigned int size = file.tellg();
	cartridgeBase = new char[size];
	file.seekg(0, std::ios::beg);
	file.read(cartridgeBase, size);
	file.close();

	MMU.initMMU(cartridgeBase);

	delete[] cartridgeBase;

	CPU.init();

	while (1)
	{
		CPU.step();
		PPU.step();
	}

	return 0;
}
