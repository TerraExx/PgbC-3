#include "PixelProcessingUnit.h"
#include "Reg_Info.h"

void PixelProcessingUnit::step()
{
	unsigned char LCDC_displayState = MMU.getReg(LCDC, LCDC_BG_DISPLAY_STATE);
	unsigned int  newCPUclock = 0;

	//////////////Temp Var////////////////////

	static unsigned char OAM_clock = 0;
	static unsigned char PT_clock = 0;
	static unsigned char HB_clock = 0;
	static unsigned char VB_clock = 0;

	//////////////////////////////////////////

	if (0 == LCDC_displayState)
	{
		PPUstate = OFF;
		lastLineDrawn = 0;
		lastPixelDrawn = 0;
		MMU.write(STAT, 0x01);
		return;
	}
	else
	{
		if ( OFF == PPUstate )
		{
			PPUstate = OAM_SEARCH;
			PPUclock = CPU.getCurrentClock();
			MMU.write(STAT, OAM_SEARCH);
			return;
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
			++PT_clock;

			if (PIXEL_TRANSFER_LAST_CLOCK == PT_clock)
			{
				PT_clock = 0;

				PPUstate = H_BLANK;
				++lastLineDrawn;
				MMU.write(STAT, H_BLANK);
			}
			break;

		case H_BLANK:
			++HB_clock;

			if (H_BLANK_LAST_CLOCK == H_BLANK_LAST_CLOCK)
			{
				HB_clock = 0;

				if (H_LINES == lastLineDrawn)
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
			++VB_clock;

			if (V_BLANK_LAST_CLOCK == VB_clock)
			{
				VB_clock = 0;

				PPUstate = OAM_SEARCH;
				lastLineDrawn = 0;
				MMU.write(STAT, OAM_SEARCH);
			}
			break;

		default:
			break;
		}

		++PPUclock;
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
