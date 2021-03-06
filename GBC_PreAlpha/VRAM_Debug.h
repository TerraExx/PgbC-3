#pragma once
#include <cstdio>
#include <vector>

#include "SDL.h"

class VRAM_Debug
{
private:
	using e_bgp = enum
	{
		BLACK   = 0x03,
		D_GREY  = 0x02,
		L_GREY  = 0x01,
		WHITE   = 0x00,
		INVALID_BG = 0xFF
	};

	//Grid lines
	const unsigned char H_SLIM_LINE_NUM = 21;
	const unsigned char V_SLIM_LINE_NUM = 30;
	const unsigned char H_BOLD_LINE_NUM = 2;
	const unsigned char V_BOLD_LINE_NUM = 1;
	const unsigned char BOLD_LINE_THICK = 2;

	//Screen scale
	const unsigned char X_SCALE = 2;
	const unsigned char Y_SCALE = 2;

	//Screen dimension constants
	const unsigned short SCREEN_WIDTH  = (8 * 16 * 2 + V_SLIM_LINE_NUM + BOLD_LINE_THICK) * X_SCALE;
	const unsigned short SCREEN_HEIGHT = (8 * 24 + H_SLIM_LINE_NUM + BOLD_LINE_THICK * H_BOLD_LINE_NUM) * Y_SCALE;

	//The window we'll be rendering to
	SDL_Window * gWindow = nullptr;

	//The window renderer
	SDL_Renderer* gRenderer = nullptr;

	//Pallet
	e_bgp P_00 = INVALID_BG;
	e_bgp P_01 = INVALID_BG;
	e_bgp P_10 = INVALID_BG;
	e_bgp P_11 = INVALID_BG;

	void updateBgPallet(unsigned char bgp);

	void drawPoint(e_bgp pallet, unsigned short x, unsigned short y);
	void drawGrid();
public:
	void draw( unsigned short tileNum, unsigned char* rows, unsigned char bgp );

	void init();

	VRAM_Debug();
	~VRAM_Debug();
};

