#include "VRAM_Debug.h"
#include "Reg_Info.h"
#include "Memory_Info.h"

void VRAM_Debug::updateBgPallet(unsigned char bgp)
{
	P_00 = static_cast<e_bgp>(bgp & BGP_00);
	P_01 = static_cast<e_bgp>((bgp & BGP_01) >> 2);
	P_10 = static_cast<e_bgp>((bgp & BGP_10) >> 4);
	P_11 = static_cast<e_bgp>((bgp & BGP_11) >> 6);
}

void VRAM_Debug::drawPoint(e_bgp pallet, unsigned short x, unsigned short y)
{
	switch (pallet)
	{
	case BLACK:
		SDL_SetRenderDrawColor(gRenderer, 13, 64, 41, 255);
		break;
	case D_GREY:
		SDL_SetRenderDrawColor(gRenderer, 27, 127, 82, 255);
		break;
	case L_GREY:
		SDL_SetRenderDrawColor(gRenderer, 40, 191, 123, 255);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(gRenderer, 53, 255, 164, 255);
		break;
	default:
		printf("Something is wrong\n");
		SDL_SetRenderDrawColor(gRenderer, 00, 00, 00, 255);
		break;
	}

	SDL_RenderDrawPoint(gRenderer, x, y);
}

void VRAM_Debug::drawGrid()
{
	unsigned short x_pos = 0;
	unsigned short y_pos = 0;

	SDL_SetRenderDrawColor(gRenderer, 195, 195, 195, 0xFF);

	//Draw Vertical Lines
	for (unsigned char Bank = 0; Bank < 2; ++Bank)
	{
		for (unsigned char LineNum = 0; LineNum < V_SLIM_LINE_NUM / 2; ++LineNum)
		{
			x_pos += 0x08;
			SDL_RenderDrawLine(gRenderer
				, x_pos
				, 0
				, x_pos
				, SCREEN_HEIGHT
			);
			++x_pos;
		}

		x_pos += 0x08;

		SDL_Rect fillRect =
		{
			x_pos,
			0,
			BOLD_LINE_THICK,
			SCREEN_HEIGHT
		};
		SDL_RenderFillRect(gRenderer, &fillRect);

		x_pos += BOLD_LINE_THICK;
	}

	//Draw Horizontal Lines
	for (unsigned char Bank = 0; Bank < 3; ++Bank)
	{
		for (unsigned char LineNum = 0; LineNum < H_SLIM_LINE_NUM / 3; ++LineNum)
		{
			y_pos += 0x08;
			SDL_RenderDrawLine(gRenderer
				, 0
				, y_pos
				, SCREEN_WIDTH
				, y_pos
			);
			++y_pos;
		}

		y_pos += 0x08;

		SDL_Rect fillRect =
		{
			0,
			y_pos,
			SCREEN_WIDTH,
			BOLD_LINE_THICK,
		};
		SDL_RenderFillRect(gRenderer, &fillRect);

		y_pos += BOLD_LINE_THICK;
	}
}

void VRAM_Debug::draw(unsigned short tileNum, unsigned char* rows, unsigned char bgp)
{
	unsigned short row;
	unsigned short bit_mask;
	unsigned short x_offset; 
	unsigned short y_offset;

	//Update BG Pallet
	updateBgPallet(bgp);

	//Draw Tile
	x_offset = 0x09 * (tileNum % 16);
	y_offset = 0x09 * (tileNum / 16) + (tileNum / 128) * (BOLD_LINE_THICK - 1);

	for (unsigned short TileRow = 0; TileRow < 8; ++TileRow)
	{
		row = (rows[0] << 8) | rows[1];
		bit_mask = 0x8080;
		rows += 2;

		for (unsigned char Pixel = 0; Pixel < 8; ++Pixel)
		{
			switch ((row & bit_mask) >> (7 - Pixel))
			{
			case 0x0000:
				drawPoint(P_00, x_offset + Pixel, y_offset);
				break;
			case 0x0001:
				drawPoint(P_01, x_offset + Pixel, y_offset);
				break;
			case 0x0100:
				drawPoint(P_10, x_offset + Pixel, y_offset);
				break;
			case 0x0101:
				drawPoint(P_11, x_offset + Pixel, y_offset);
				break;
			}

			bit_mask = bit_mask >> 1;
		}

		++y_offset;
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

VRAM_Debug::VRAM_Debug()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("VRAM Debug", 1300, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Set Scale
				SDL_RenderSetScale(gRenderer, X_SCALE, Y_SCALE);

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				drawGrid();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
}


VRAM_Debug::~VRAM_Debug()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
