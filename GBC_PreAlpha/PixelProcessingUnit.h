#pragma once
#include <queue>
#include "SDL.h"

#include "MemoryManagementUnit.h"
#include "CentralProcessingUnit.h"

class PixelProcessingUnit
{
private:
	MemoryManagementUnit  &MMU;
	CentralProcessingUnit &CPU;

	const unsigned short V_LINES = 160;
	const unsigned short H_LINES = 144;

	const unsigned char X_SCALE = 2;
	const unsigned char Y_SCALE = 2;

	const unsigned short SCREEN_WIDTH = V_LINES * X_SCALE;
	const unsigned short SCREEN_HEIGHT = H_LINES * Y_SCALE;

	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;

	using e_ppu_state = enum {
		H_BLANK,
		V_BLANK,
		OAM_SEARCH,
		PIXEL_TRANSFER,
		OFF
	};

	using e_fetcher_state = enum {
		GET_TILE_NUM,
		GET_1_ST_BYTE,
		GET_2_ND_BYTE
	};

	using s_fifo_pixel_info = struct
	{
		unsigned char value;

		unsigned char posX;
		unsigned char posY;
	};

	using e_bgp = enum
	{
		BLACK = 0x03,
		D_GREY = 0x02,
		L_GREY = 0x01,
		WHITE = 0x00,
		INVALID_BG = 0xFF
	};

	const unsigned int FRAME_LAST_CLOCK = 70224;

	//const unsigned char H_BLANK_LAST_CLOCK = 203;
	//const unsigned char V_BLANK_LAST_CLOCK = FRAME_LAST_CLOCK - (H_BLANK_LAST_CLOCK + OAM_LAST_CLOCK + PIXEL_TRANSFER_LAST_CLOCK) * H_LINES;
	//const unsigned char OAM_LAST_CLOCK = 79;
	//const unsigned char PIXEL_TRANSFER_LAST_CLOCK = 172;
	const unsigned int OAM_LAST_CLOCK = 79;
	const unsigned int PIXEL_TRANSFER_LAST_CLOCK = OAM_LAST_CLOCK + 172;
	const unsigned int H_BLANK_LAST_CLOCK = PIXEL_TRANSFER_LAST_CLOCK + 203;
	const unsigned int V_BLANK_LAST_CLOCK = FRAME_LAST_CLOCK - (H_BLANK_LAST_CLOCK + OAM_LAST_CLOCK + PIXEL_TRANSFER_LAST_CLOCK) * H_LINES;

	e_ppu_state PPUstate = OFF;
	unsigned int PPUclock = 0;
	unsigned int PPUclockCurFrame = 0;
	unsigned int firstPixelClock = 0;

	unsigned char viewPort_X = 0;
	unsigned char viewPort_Y = 0;

	unsigned char lineBeingDrawn = 0;
	unsigned char pixelBeingDrawn = 0;
	unsigned char pixelDropped = 0;

	std::queue<s_fifo_pixel_info> FIFO;

	bool runPixelFetcher = false;
	e_fetcher_state fetcherState = GET_TILE_NUM;
	unsigned short	fetchetTileNum = 0;
	unsigned short	fetchetTileCode = 0;
	unsigned char   fetchetByte[2] = { 0, 0 };

	void reset();
	void init();

	void FIFO_step();

	void updateViewPort();
	void fetcher_step();
	void fetcherUpdateTileNum();
	unsigned char fetcherGetTileCode(unsigned short offset);
	unsigned char fetcherGetByte(unsigned char byteNum);
	void fetcherPushLine();

	void drawPoint(e_bgp pallet, unsigned short x, unsigned short y);
	void renderLine();
public:
	void step();
	void step_try_2();

	PixelProcessingUnit(MemoryManagementUnit &MMU, CentralProcessingUnit &CPU);
	~PixelProcessingUnit();
};

