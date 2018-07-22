#include "PixelProcessingUnit.h"
#include "Reg_Info.h"
#include "Memory_Info.h"
#include "Video_Debug.h"

void PixelProcessingUnit::reset()
{
	PPUstate = OFF;
	MMU.write(STAT, 0x01);
}

void PixelProcessingUnit::init()
{
	PPUclock = CPU.getCurrentClock();
	firstPixelClock = PPUclock;
	runPixelFetcher = true;

	PPUstate = OAM_SEARCH;
	MMU.write(STAT, OAM_SEARCH);

	//viewPort_X = 32;
	//viewPort_Y = 25;
	viewPort_X = MMU.getReg(SCX);
	viewPort_Y = MMU.getReg(SCY);

	fetcherUpdateTileNum();

	lineBeingDrawn = 0;
	pixelBeingDrawn = 0;

	fetcherState = GET_TILE_NUM;

	MMU.write(LY, lineBeingDrawn);
}

void PixelProcessingUnit::updateViewPort()
{
	//unsigned char viewPort_X_new = viewPort_X;
	//unsigned char viewPort_Y_new = viewPort_Y;
	unsigned char viewPort_X_new = MMU.getReg(SCX);
	unsigned char viewPort_Y_new = MMU.getReg(SCY);

	if (viewPort_X < viewPort_X_new)
	{
		++viewPort_X;
	}
	else if (viewPort_X > viewPort_X_new)
	{
		--viewPort_X;
	}

	if (viewPort_Y < viewPort_Y_new)
	{
		++viewPort_Y;
	}
	else if (viewPort_Y > viewPort_Y_new)
	{
		--viewPort_Y;
	}

#ifdef BGD_DEBUG
	// ReDraw Viewport
	BGD_1_D.drawView(viewPort_X, viewPort_Y);
#endif
}

void PixelProcessingUnit::FIFO_step()
{
	if (FIFO.size() > 8)
	{
		/* Get pixel info and draw it */
		s_fifo_pixel_info pixel = FIFO.front();
		FIFO.pop();

		if (pixel.posX < viewPort_X)
		{
			++pixelDropped;
		}
		else
		{
			drawPoint(static_cast<e_bgp>(pixel.value), pixelBeingDrawn, lineBeingDrawn);

			++pixelBeingDrawn;

			////Update screen
			//SDL_RenderPresent(Renderer);
		}
	}

	return;
}

void PixelProcessingUnit::fetcher_step()
{
	if (FIFO.size() > 8)
	{
		return;
	}

	switch (fetcherState)
	{
	case GET_TILE_NUM:
		fetchetTileCode = fetcherGetTileCode(fetchetTileNum);

		fetcherState = GET_1_ST_BYTE;
		break;
	case GET_1_ST_BYTE:
		fetchetByte[0] = fetcherGetByte(0);

		fetcherState = GET_2_ND_BYTE;
		break;
	case GET_2_ND_BYTE:
		fetchetByte[1] = fetcherGetByte(1);

		fetcherPushLine();
		++fetchetTileNum;

		fetcherState = GET_TILE_NUM;
		break;
	}

}

void PixelProcessingUnit::fetcherUpdateTileNum()
{
	unsigned char offsetX = (viewPort_X + pixelDropped + pixelBeingDrawn) % 256;
	unsigned char offsetY = (viewPort_Y + lineBeingDrawn) % 256;

	fetchetTileNum = (offsetX) / 8 + ((offsetY) / 8) * 32;
}

unsigned char PixelProcessingUnit::fetcherGetTileCode(unsigned short offset)
{
	unsigned char LCDC_BG_MAP_ADDR = MMU.getReg(LCDC, LCDC_BG_CODE_AREA);

	if (0 == LCDC_BG_MAP_ADDR)
	{
		return MMU.read(BGD1_OFFSET + offset);
	}
	else
	{
		return MMU.read(BGD2_OFFSET + offset);
	}
}

unsigned char PixelProcessingUnit::fetcherGetByte(unsigned char byteNum)
{
	unsigned char LCDC_BG_TILE_ADDR = MMU.getReg(LCDC, LCDC_BG_CHARACTER_DATA);

	if (1 == LCDC_BG_TILE_ADDR)
	{
		unsigned char lineOffset = (((viewPort_Y + lineBeingDrawn) % 256) % 8) * 2;

		return MMU.read(CRAM_OFFSET + 0x10 * fetchetTileNum + lineOffset + byteNum);
	}
	else
	{
		// TODO Implement the other tile address fetching
		return 0;
	}
}

void PixelProcessingUnit::fetcherPushLine()
{
	unsigned short row = (fetchetByte[0] << 8) | fetchetByte[1];
	unsigned short bit_mask = 0x8080;
	s_fifo_pixel_info fifoPixel;

	for (char Pixel = 0; Pixel < 8; ++Pixel)
	{
		fifoPixel.value = (row & bit_mask) >> (7 - Pixel);
		fifoPixel.value = (fifoPixel.value & 0x01) | fifoPixel.value >> 1;

		fifoPixel.posX = (fetchetTileNum % 32) * 8 + Pixel;
		fifoPixel.posY = (fetchetTileNum / 32) * 8 + lineBeingDrawn;

		FIFO.push(fifoPixel);
		bit_mask = bit_mask >> 1;
	}
}

void PixelProcessingUnit::drawPoint(e_bgp pallet, unsigned short x, unsigned short y)
{
	switch (pallet)
	{
	case BLACK:
		SDL_SetRenderDrawColor(Renderer, 13, 64, 41, 255);
		break;
	case D_GREY:
		SDL_SetRenderDrawColor(Renderer, 27, 127, 82, 255);
		break;
	case L_GREY:
		SDL_SetRenderDrawColor(Renderer, 40, 191, 123, 255);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(Renderer, 53, 255, 164, 255);
		break;
	default:
		printf("Something is wrong\n");
		SDL_SetRenderDrawColor(Renderer, 00, 00, 00, 255);
		break;
	}

	SDL_RenderDrawPoint(Renderer, x, y);
}

void PixelProcessingUnit::renderLine()
{
	unsigned short newFetchetTileNum = fetchetTileNum;
	unsigned short tileCode = 0;
	unsigned char  tileRow[2] = { 0, 0 };
	unsigned char  pixelLine[168] = {0};
	unsigned char  *pixelLinePtr = pixelLine;
	unsigned short row = 0;
	unsigned short bit_mask = 0;
	unsigned short value = 0;

	for (char tileNum = 0; tileNum < 21; ++tileNum)
	{
		if (tileNum != 0)
		{
			++newFetchetTileNum;
			if ((newFetchetTileNum % 32) == 0)
			{
				newFetchetTileNum -= 32;
			}
		}

		tileCode = MMU.read(BGD1_OFFSET + newFetchetTileNum);

		if (tileCode != 0)
		{
			char proba = 0;
			proba++;
		}

		tileRow[0] =
			MMU.read(CRAM_OFFSET + tileCode * 0x10 + ((viewPort_Y + lineBeingDrawn) % 8) * 0x02);
		tileRow[1] =
			MMU.read(CRAM_OFFSET + tileCode * 0x10 + ((viewPort_Y + lineBeingDrawn) % 8) * 0x02 + 1);

		row = (tileRow[0] << 8) | tileRow[1];
		bit_mask = 0x8080;

		for (char Pixel = 0; Pixel < 8; ++Pixel)
		{
			value = (row & bit_mask) >> (7 - Pixel);
			value = (value & 0x01) | value >> 7;

			bit_mask = bit_mask >> 1;
			*pixelLinePtr = value;
			++pixelLinePtr;
		}
	}

	pixelLinePtr = pixelLine + viewPort_X % 8;

	for (unsigned char pixel = 0; pixel < 160; ++pixel)
	{
		drawPoint(static_cast<e_bgp>(*pixelLinePtr), pixel, lineBeingDrawn);
		++pixelLinePtr;
	}
}

void PixelProcessingUnit::step()
{
	unsigned char LCDC_displayState = MMU.getReg(LCDC, LCDC_DISPLAY_ENABLE);
	unsigned int  newCPUclock = 0;

	//////////////Temp Var////////////////////
	static unsigned char OAM_clock = 0;
	static unsigned char HB_clock = 0;
	static unsigned char VB_clock = 0;

	static unsigned int  frameDrawDuration = 0;
	//////////////////////////////////////////

	if (0 == LCDC_displayState)
	{
		reset();
		return;
	}
	else
	{
		if (OFF == PPUstate)
		{
			init();
		}
	}

	newCPUclock = CPU.getCurrentClock();

	while (PPUclock != newCPUclock)
	{
		switch (PPUstate)
		{
		case OAM_SEARCH:
			//TODO Implement Sprite Drawing
			++OAM_clock;

			if (OAM_LAST_CLOCK == OAM_clock)
			{
				OAM_clock = 0;

				PPUstate = PIXEL_TRANSFER;
				MMU.write(STAT, PIXEL_TRANSFER);
			}
			break;

		case PIXEL_TRANSFER:
			if (runPixelFetcher == true)
			{
				runPixelFetcher = false;

				FIFO_step();
				fetcher_step();
			}
			else
			{
				runPixelFetcher = true;

				FIFO_step();
			}

			if (pixelBeingDrawn == (V_LINES + 1))
			{
				PPUstate = H_BLANK;
				MMU.write(STAT, H_BLANK);

				pixelDropped = 0;
				pixelBeingDrawn = 0;
				++lineBeingDrawn;
				MMU.write(LY, lineBeingDrawn);

				updateViewPort();
				fetcherUpdateTileNum();

				while (!FIFO.empty())
				{
					FIFO.pop();
				}
			}
			break;

		case H_BLANK:
			++HB_clock;

			if (H_BLANK_LAST_CLOCK == H_BLANK_LAST_CLOCK)
			{
				HB_clock = 0;

				if ((V_LINES + 1) == lineBeingDrawn)
				{
					PPUstate = V_BLANK;
					MMU.write(STAT, V_BLANK);
				}
				else
				{
					PPUstate = OAM_SEARCH;
					MMU.write(STAT, OAM_SEARCH);
				}
			}
			break;

		case V_BLANK:
			if (VB_clock == 0)
			{
				//Update screen
				SDL_RenderPresent(Renderer);

				frameDrawDuration = PPUclock - firstPixelClock;
			}

			++VB_clock;

			if ((FRAME_LAST_CLOCK - frameDrawDuration) == VB_clock)
			{
				VB_clock = 0;

				PPUstate = OAM_SEARCH;
				MMU.write(STAT, OAM_SEARCH);

				firstPixelClock = PPUclock + 1;
				lineBeingDrawn = 0;
			}
			break;

		default:
			break;
		}

		++PPUclock;
	}
}

void PixelProcessingUnit::step_try_2()
{
	unsigned char LCDC_displayState = MMU.getReg(LCDC, LCDC_DISPLAY_ENABLE);
	unsigned int  newCPUclock = 0;
	e_ppu_state   newPPUstate = OFF;

	if (0 == LCDC_displayState)
	{
		if (OFF != PPUstate)
		{
			reset();
			PPUclockCurFrame = 0;
		}
		return;
	}
	else
	{
		if (OFF == PPUstate)
		{
			init();
		}
	}

	newCPUclock = CPU.getCurrentClock();
	PPUclockCurFrame += newCPUclock - PPUclock;
	PPUclock = newCPUclock;

	if ((PPUclockCurFrame % 456) < OAM_LAST_CLOCK)
	{
		newPPUstate = OAM_SEARCH;
	}
	else if ((PPUclockCurFrame % 456) < PIXEL_TRANSFER_LAST_CLOCK)
	{
		newPPUstate = PIXEL_TRANSFER;
	}
	else if ((PPUclockCurFrame % 456) < H_BLANK_LAST_CLOCK)
	{
		newPPUstate = H_BLANK;
	}

	if (newPPUstate != PPUstate)
	{
		if (PPUstate == V_BLANK)
		{
			lineBeingDrawn = (PPUclockCurFrame / 456);
			MMU.write(LY, lineBeingDrawn);

			if (PPUclockCurFrame > FRAME_LAST_CLOCK)
			{
				PPUclockCurFrame = PPUclockCurFrame % FRAME_LAST_CLOCK;

				lineBeingDrawn = 0;
				MMU.write(LY, lineBeingDrawn);

				updateViewPort();
				fetchetTileNum =
					(viewPort_X) / 8 + (((viewPort_Y + lineBeingDrawn) % 256) / 8) * 32;

				PPUstate = OAM_SEARCH;
				MMU.write(STAT, OAM_SEARCH);
			}
		}
		else
		{
			switch (newPPUstate)
			{
			case OAM_SEARCH:
				lineBeingDrawn = (PPUclockCurFrame / 456);
				MMU.write(LY, lineBeingDrawn);

				updateViewPort();
				fetchetTileNum =
					(viewPort_X) / 8 + (((viewPort_Y + lineBeingDrawn) % 256) / 8) * 32;

				if (lineBeingDrawn == 144)
				{
					//Update screen
					SDL_RenderPresent(Renderer);

					PPUstate = V_BLANK;
					MMU.write(STAT, V_BLANK);
				}
				else
				{
					PPUstate = OAM_SEARCH;
					MMU.write(STAT, OAM_SEARCH);
				}
				break;

			case PIXEL_TRANSFER:
				PPUstate = PIXEL_TRANSFER;
				MMU.write(STAT, PIXEL_TRANSFER);
				break;

			case H_BLANK:
				renderLine();

				PPUstate = H_BLANK;
				MMU.write(STAT, H_BLANK);
				break;
			}
		}
	}
}

PixelProcessingUnit::PixelProcessingUnit(MemoryManagementUnit &MMU, CentralProcessingUnit &CPU)
	: MMU(MMU),
	CPU(CPU)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		Window = SDL_CreateWindow("PgbC-3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Set Scale
				SDL_RenderSetScale(Renderer, X_SCALE, Y_SCALE);

				//Clear screen
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);

				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	}
}


PixelProcessingUnit::~PixelProcessingUnit()
{
	//Destroy window
	SDL_DestroyWindow(Window);
	Window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
