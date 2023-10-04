#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[])
{
	// TODO: Initialise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Create a window with the specified name, anywhere on the screen, 800x600 pixel size and no SDL_WindowFlags flags.
	SDL_Window* sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);

	// TODO: Error checking
	if (sdlWindow == nullptr)
	{
		std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
	}

	(void)getchar();

	// TODO: Clean up
	SDL_DestroyWindow(sdlWindow); // Opposite of SDL_CreateWindow(...)
	SDL_Quit(); // Opposite of SDL_Init(...)

	return 0;
}