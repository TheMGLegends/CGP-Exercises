#include <iostream>
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

	for (int frameCount = 0; frameCount < 850; frameCount++) 
	{
		// TODO: Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);

		// TODO: Create a destination for where the image will be copied {x, y, w, h}
		SDL_Rect destinationRect{ frameCount, 25, 16, 16 };

		// TODO: Copy the texture onto the rendering target
		SDL_RenderCopy(g_sdlRenderer, doorTexture, NULL, &destinationRect);

		// TODO: Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);

		// TODO: Halt execution for 16 milliseconds (approx. 60 frames per second)
		SDL_Delay(16);
	}

	// TODO: Clean up
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyRenderer(g_sdlRenderer); // Opposite of SDL_CreateRenderer(...)
	SDL_DestroyWindow(g_sdlWindow); // Opposite of SDL_CreateWindow(...)
	SDL_Quit(); // Opposite of SDL_Init(...)

	return 0;
}