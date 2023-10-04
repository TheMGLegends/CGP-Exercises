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

	// TODO: Load door.bmp as a surface
	SDL_Surface* image = SDL_LoadBMP("Assets/door.bmp");
	if (image == nullptr)
	{
		std::cout << "Failed to load door.bmp. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Load crusader.bmp as a surface
	SDL_Surface* image2 = SDL_LoadBMP("Assets/crusader.bmp");
	if (image2 == nullptr)
	{
		std::cout << "Failed to load crusader.bmp. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Get a pointer to the windows surface so we can draw to it
	SDL_Surface* windowSurface = SDL_GetWindowSurface(sdlWindow);
	if (windowSurface == nullptr)
	{
		std::cout << "Failed to get window surface. SDL error: " << SDL_GetError() << std::endl;
	}

	// TODO: Memory Management (Exercise 3) 
	// TODO: Testing how loading an image onto the SDL_Surface and clearing it affects memory
	for (int i = 0; i < 1000; i++)
	{
		// TODO: Create a destination for where the image will be copied onto the window surface {x, y, w, h}
		SDL_Rect destinationRect{ 400, 300, 16, 16 };
		SDL_Rect destinationRect2{ 200, 300, 64, 80 };

		// TODO: Blit (Copy) the image onto the window surface
		SDL_BlitSurface(image, NULL, windowSurface, &destinationRect);
		SDL_BlitSurface(image2, NULL, windowSurface, &destinationRect2);

		// TODO: Update the window to reflect the changes
		SDL_UpdateWindowSurface(sdlWindow);
	}

	// TODO: Halt the program until enter is pressed in the console
	(void)getchar();

	// TODO: Clean up
	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_DestroyWindow(sdlWindow); // Opposite of SDL_CreateWindow(...)
	SDL_Quit(); // Opposite of SDL_Init(...)

	return 0;
}