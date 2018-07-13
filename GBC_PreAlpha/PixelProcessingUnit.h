#pragma once
#include <queue>

#include "MemoryManagementUnit.h"

class PixelProcessingUnit
{
private:
	MemoryManagementUnit &MMU;

	using e_ppu_state = enum {
		OAM_SEARCH,
		PIXEL_TRANSFER,
		H_BLANK,
		V_BLANK
	};

	const unsigned char MAX_CLOCK = 114;

	e_ppu_state state;
	unsigned char clock;

	std::queue<unsigned char> FIFO;



public:
	void step();

	PixelProcessingUnit(MemoryManagementUnit &MMU);
	~PixelProcessingUnit();
};

