#include <iostream>

#include "BGD_Debug.h"
#include "Reg_Info.h"

void BGD_Debug::updateBgPallet(unsigned char bgp)
{
	P_00 = static_cast<e_bgp>(bgp & BGP_00);
	P_01 = static_cast<e_bgp>((bgp & BGP_01) >> 2);
	P_10 = static_cast<e_bgp>((bgp & BGP_10) >> 4);
	P_11 = static_cast<e_bgp>((bgp & BGP_11) >> 6);
}

void BGD_Debug::drawPoint(e_bgp pallet, unsigned short x, unsigned short y)
{
	switch (pallet)
	{
	case BLACK:
		SDL_SetRenderDrawColor(RendererBg, 13, 64, 41, 255);
		break;
	case D_GREY:
		SDL_SetRenderDrawColor(RendererBg, 27, 127, 82, 255);
		break;
	case L_GREY:
		SDL_SetRenderDrawColor(RendererBg, 40, 191, 123, 255);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(RendererBg, 53, 255, 164, 255);
		break;
	default:
		printf("Something is wrong\n");
		SDL_SetRenderDrawColor(RendererBg, 00, 00, 00, 255);
		break;
	}

	SDL_RenderDrawPoint(RendererBg, x, y);
}

void BGD_Debug::drawGrid()
{
	unsigned short x_pos = 0;
	unsigned short y_pos = 0;

	SDL_SetRenderDrawColor(RendererBg, 195, 195, 195, 0xFF);

	//Draw Vertical Lines
	for (unsigned char LineNum = 0; LineNum < V_SLIM_LINE_NUM; ++LineNum)
	{
		x_pos += 0x08;
		SDL_RenderDrawLine(RendererBg
			, x_pos
			, 0
			, x_pos
			, SCREEN_HEIGHT
		);
		++x_pos;
	}

	//Draw Horizontal Lines
	for (unsigned char LineNum = 0; LineNum < H_SLIM_LINE_NUM; ++LineNum)
	{
		y_pos += 0x08;
		SDL_RenderDrawLine(RendererBg
			, 0
			, y_pos
			, SCREEN_WIDTH
			, y_pos
		);
		++y_pos;
	}

}

void BGD_Debug::drawBg(unsigned short tileNum, unsigned char* rows, unsigned char bgp)
{
	unsigned short row;
	unsigned short bit_mask;
	unsigned short x_offset;
	unsigned short y_offset;

	//Update BG Pallet
	updateBgPallet(bgp);

	//Draw Tile
	x_offset = 0x09 * (tileNum % 32);
	y_offset = 0x09 * (tileNum / 32);


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

	// Save Background
	if (SDL_RenderReadPixels(RendererBg, &ScreenShot->clip_rect, ScreenShot->format->format, ScreenShot->pixels, ScreenShot->w * ScreenShot->format->BytesPerPixel) != 0)
	{
		std::cout << "Read Pixels ne radi" << std::endl;
	}

	//Update screen
	SDL_RenderPresent(RendererBg);
}

void BGD_Debug::drawView(unsigned char posX, unsigned char posY)
{
	// ReDraw background
	SDL_Texture* Texture = NULL;
	Texture = SDL_CreateTextureFromSurface(RendererBg, ScreenShot);
	SDL_RenderCopy(RendererBg, Texture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(RendererBg);

	// Draw Viewport
	SDL_Rect outlineRect = { posX, posY, 160 + 160/8, 144 + 144/8 };
	SDL_SetRenderDrawColor(RendererBg, 0xff, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(RendererBg, &outlineRect);

	//Update screen
	SDL_RenderPresent(RendererBg);
}

void BGD_Debug::init()
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
		Window = SDL_CreateWindow("BGD Debug", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Update surface
			ScreenShot = SDL_GetWindowSurface(Window);

			//Create Background renderer for window
			RendererBg = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (RendererBg == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Set Scale
				SDL_RenderSetScale(RendererBg, X_SCALE, Y_SCALE);

				//Clear screen
				SDL_SetRenderDrawColor(RendererBg, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(RendererBg);
				drawGrid();

				//Update screen
				SDL_RenderPresent(RendererBg);
			}
		}
	}
}

BGD_Debug::BGD_Debug()
{
}


BGD_Debug::~BGD_Debug()
{
}
