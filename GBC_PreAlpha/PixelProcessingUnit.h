#pragma once
#include <queue>
#include "SDL.h"

#include "MemoryManagementUnit.h"
#include "CentralProcessingUnit.h"

class PixelProcessingUnit
{
private:
	const unsigned short V_LINES = 160;
	const unsigned short H_LINES = 144;

	const unsigned char X_SCALE = 2;
	const unsigned char Y_SCALE = 2;

	const unsigned short SCREEN_WIDTH = V_LINES * X_SCALE;
	const unsigned short SCREEN_HEIGHT = H_LINES * Y_SCALE;

	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;

	MemoryManagementUnit &MMU;
	CentralProcessingUnit &CPU;

	using e_ppu_state = enum {
		H_BLANK,
		V_BLANK,
		OAM_SEARCH,
		PIXEL_TRANSFER,
		OFF
	};

	const unsigned char H_BLANK_LAST_CLOCK = 203;
	const unsigned char V_BLANK_LAST_CLOCK = 70224 - (H_BLANK_LAST_CLOCK + OAM_LAST_CLOCK + PIXEL_TRANSFER_LAST_CLOCK) * H_LINES;
	const unsigned char OAM_LAST_CLOCK = 79;
	const unsigned char PIXEL_TRANSFER_LAST_CLOCK = 172;

	e_ppu_state PPUstate = OFF;
	unsigned short PPUclock = 0;
	unsigned char lastLineDrawn = 0;
	unsigned char lastPixelDrawn = 0;

	std::queue<unsigned char> FIFO;

public:
	void step();

	PixelProcessingUnit(MemoryManagementUnit &MMU, CentralProcessingUnit &CPU);
	~PixelProcessingUnit();
};

