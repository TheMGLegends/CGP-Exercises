#include <iostream>
#include <stdlib.h>
#include "SDL.h"

SDL_Window* g_sdlWindow;
SDL_Renderer* g_sdlRenderer;

SDL_Texture* LoadTexture(const char* filename) 
{
	// TODO: Load door.bmp as a surface
	SDL_Surface* image = SDL_LoadBMP(filename);
	// TODO: Error checking
	if (image == nullptr)
	{
		std::cout << "Failed to load " << filename << " .SDL error : " << SDL_GetError() << std::endl;
	}

	// TODO: Convert surface of the loaded bmp into a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_sdlRenderer, image);
	// TODO: Error checking
	if (texture == nullptr)
	{
		std::cout << "Failed to create texture from surface. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Free the surface - as we created a texture from, it, we intend to use the texture and no longer need the surface
	SDL_FreeSurface(image);

	return texture;
}

int main(int argc, char* argv[])
{
	srand(unsigned int(time(NULL)));

	// TODO: Initialise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Create a window with the specified name, anywhere on the screen, 800x600 pixel size and no SDL_WindowFlags flags.
	g_sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);

	// TODO: Error checking
	if (g_sdlWindow == nullptr)
	{
		std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Create a rendering context for our window. Enable hardware acceleration with the SDL_RENDERER_ACCELERATED flag
	g_sdlRenderer = SDL_CreateRenderer(g_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	// TODO: Error checking
	if (g_sdlRenderer == nullptr)
	{
		std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* doorTexture = LoadTexture("Assets/door.bmp");
	SDL_Texture* crusaderTexture = LoadTexture("Assets/crusader.bmp");
	//SDL_Texture* fishTexture = LoadTexture("Assets/fish_blue1.bmp");

	// TODO: Creating texture without a surface
	SDL_Texture* textureWithoutSurface = SDL_CreateTexture(g_sdlRenderer, SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_TARGET, 20, 20);

	// TODO: Changing texture pixel data manually
	SDL_SetRenderTarget(g_sdlRenderer, textureWithoutSurface);

	// TODO: Change background colour of renderer
	SDL_SetRenderDrawColor(g_sdlRenderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);

	SDL_Rect destinationForTWS{ 5, 5, 10, 10 };

	SDL_RenderFillRect(g_sdlRenderer, &destinationForTWS);

	SDL_SetRenderTarget(g_sdlRenderer, NULL);

	SDL_SetRenderDrawColor(g_sdlRenderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);

	bool keepRunning = true;

	int keyboardX = 0;
	int keyboardY = 0;

	int mouseX = 100;
	int mouseY = 100;

	int movementSpeed = 5;

	while (keepRunning)
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent)) 
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				keepRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					keepRunning = false;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_w)
				{
					keyboardY -= movementSpeed;
					//--Y;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_s)
				{
					keyboardY += movementSpeed;
					//++Y;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_a)
				{
					keyboardX -= movementSpeed;
					//--X;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_d)
				{
					keyboardX += movementSpeed;
					//++X;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (sdlEvent.button.clicks == SDL_BUTTON_LEFT)
				{
					std::cout << "Left mouse button pressed!" << std::endl;
				}
				break;
			case SDL_MOUSEMOTION:
				std::cout << "X = " << sdlEvent.motion.x << "\n" << "Y = " << sdlEvent.motion.y << std::endl;
				mouseX = sdlEvent.motion.x;
				mouseY = sdlEvent.motion.y;
				break;
			default:
				break;
			}
		}

		// TODO: Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);

		// TODO: Create a destination for where the image will be copied {x, y, w, h}
		SDL_Rect destinationRect{ 0, 0, 32, 32 };
		SDL_Rect destinationRect2{ keyboardX, keyboardY, 40, 40 };
		SDL_Rect destinationRect3{ mouseX - 16, mouseY - 16, 32, 32 };

		// TODO: Copy the texture onto the rendering target
		SDL_RenderCopy(g_sdlRenderer, doorTexture, NULL, &destinationRect);
		SDL_RenderCopy(g_sdlRenderer, crusaderTexture, NULL, &destinationRect2);
		SDL_RenderCopy(g_sdlRenderer, textureWithoutSurface, NULL, &destinationRect3);

		// TODO: Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);

		// TODO: Halt execution for 16 milliseconds (approx. 60 frames per second)
		SDL_Delay(16);
	}

	// TODO: Clean up
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(crusaderTexture);
	SDL_DestroyTexture(textureWithoutSurface);
	SDL_DestroyRenderer(g_sdlRenderer); // Opposite of SDL_CreateRenderer(...)
	SDL_DestroyWindow(g_sdlWindow); // Opposite of SDL_CreateWindow(...)
	SDL_Quit(); // Opposite of SDL_Init(...)

	return 0;
}