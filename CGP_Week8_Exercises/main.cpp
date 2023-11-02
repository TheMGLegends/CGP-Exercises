#include <iostream>
#include <stdlib.h>
#include "Factory.h"
#include "GameObject.h"
#include "Time.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Collision.h"
#include <vector>

SDL_Window* g_sdlWindow;
SDL_Renderer* g_sdlRenderer;
TTF_Font* g_font;

const int SCREEN_W = 1000;
const int SCREEN_H = 1000;

int g_fontPSize = 32;
int g_cameraX = 0;
int g_cameraY = 0;

float g_zoomInOut = 2;

SDL_Texture* LoadTexture(const char* filename)
{
	// TODO: Load door.bmp as a surface
	//SDL_Surface* image = SDL_LoadBMP(filename);
	SDL_Surface* image = IMG_Load(filename);
	// TODO: Error checking
	if (image == nullptr)
	{
		std::cout << "Failed to load " << filename << " .SDL error : " << IMG_GetError() << std::endl;
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

bool Initialise() {
	// TODO: Create a window with the specified name, anywhere on the screen, 800x600 pixel size and no SDL_WindowFlags flags.
	g_sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, NULL);

	// TODO: Error checking
	if (g_sdlWindow == nullptr)
	{
		std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
		return true;
	}

	// TODO: Create a rendering context for our window. Enable hardware acceleration with the SDL_RENDERER_ACCELERATED flag
	g_sdlRenderer = SDL_CreateRenderer(g_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	// TODO: Error checking
	if (g_sdlRenderer == nullptr)
	{
		std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
		return true;
	}
	
	// TODO: Initialise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL error: " << SDL_GetError() << std::endl;
		return true;
	}

	// TODO: Initialise SDL Image
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int initted = IMG_Init(flags);

	if (initted != flags) 
	{
		std::cout << "Failed to initialise SDL_Image error: " << IMG_GetError() << std::endl;
		return true;
	}

	// TODO: Initialise SDL Mixer
	flags = MIX_INIT_MP3;
	initted = Mix_Init(flags);

	if (initted != flags)
	{
		std::cout << "Failed to initialise SDL_Mixer error: " << Mix_GetError() << std::endl;
		return true;
	}

	// TODO: Open Audio Device
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) 
	{
		std::cout << "Failed to open audio device. SDL_Mixer error: " << Mix_GetError() << std::endl;
		return true;
	}

	// TODO: Initialise SDL TTF
	if (TTF_Init() < 0) {
		std::cout << "Failed to initialise TTF. SDL_TTF error: " << TTF_GetError() << std::endl;
		return true;
	}

	// TODO: Load Font
	g_font = TTF_OpenFont("Assets/8bitOperatorPlus8-Regular.ttf", g_fontPSize);
	if (g_font == nullptr) {
		std::cout << "TTF failed to load font. SDL_TTF error: " << TTF_GetError() << std::endl;
		return true;
	}

	return false;
}

void CleanUp() {
	// TODO: Clean up
	//SDL_DestroyTexture(doorTexture);
	//SDL_DestroyTexture(crusaderTexture);
	SDL_DestroyRenderer(g_sdlRenderer); // Opposite of SDL_CreateRenderer(...)
	SDL_DestroyWindow(g_sdlWindow); // Opposite of SDL_CreateWindow(...)
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_Quit(); // Opposite of SDL_Init(...)

}

void AutoResizeTextWidthAndHeight(const char* text, int &textWidth, int &textHeight) {
	int size = 0;

	while (text[size] != '\0') size++;

	textHeight = g_fontPSize;
	textWidth = size * textHeight;
}


int main(int argc, char* argv[])
{
	srand(unsigned int(time(NULL)));

	// TODO: Collision Test
	//if (Collision::CircleCollision(10, 10, 1, 3, 2, 0.5f)) {
	//	std::cout << "Overlap Detected!" << std::endl;
	//}
	//else {
	//	std::cout << "No overlap!" << std::endl;
	//}

	Factory factory{};

	int textWidth = 0;
	int textHeight = 0;

	if (Initialise()) {
		std::cout << "Application failed to initialise. Quitting..." << std::endl;
		return -1;
	}

	// TODO: Load SFX
	Mix_Chunk* coinSFX = Mix_LoadWAV("Assets/Coin01.wav");
	Mix_VolumeChunk(coinSFX, 25);

	// TODO: Load Music
	Mix_Music* music = Mix_LoadMUS("Assets/rng_lo-fi_loop.mp3");
	// TODO: Music playing infinitely
	//Mix_PlayMusic(music, -1);
	Mix_FadeInMusic(music, -1, 5000);
	Mix_VolumeMusic(50);

	const char* text = "Hello World!";

	// TODO: Create texture:
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, text, { 255, 215, 0, 255 });
	AutoResizeTextWidthAndHeight(text, textWidth, textHeight);
	SDL_Rect fontDstRect{ 0, 500, textWidth, textHeight };
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_Texture* doorTexture = LoadTexture("Assets/door.png");
	//SDL_Texture* crusaderTexture = LoadTexture("Assets/crusader.bmp");
	SDL_Texture* pngTexture = LoadTexture("Assets/door.png");
	GameObject sword = factory.CreateGameObject(pngTexture, false);
	GameObject door = factory.CreateGameObject(doorTexture, true);

	std::vector<GameObject> gameObjectList;

	gameObjectList.push_back(sword);
	gameObjectList.push_back(door);

	//GameObject sword{ pngTexture };
	
	//SDL_Texture* fishTexture = LoadTexture("Assets/fish_blue1.bmp");

	// TODO: Creating texture without a surface
	SDL_Texture* textureWithoutSurface = SDL_CreateTexture(g_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);

	// TODO: Changing texture pixel data manually
	SDL_SetRenderTarget(g_sdlRenderer, textureWithoutSurface);

	// TODO: Change background colour of renderer
	SDL_SetRenderDrawColor(g_sdlRenderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);


	SDL_Rect destinationForTWS{ 5, 5, 10, 10 };

	SDL_RenderFillRect(g_sdlRenderer, &destinationForTWS);

	SDL_RenderClear(g_sdlRenderer);

	SDL_SetRenderTarget(g_sdlRenderer, NULL);

	SDL_SetRenderDrawColor(g_sdlRenderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);

	bool keepRunning = true;

	bool keyW = 0;
	bool keyS = 0;
	bool keyA = 0;
	bool keyD = 0;

	int keyboardX = 0;
	int keyboardY = 0;

	int arrowX = 100;
	int arrowY = 100;

	int mouseX = 100;
	int mouseY = 100;

	int movementSpeed = 200;

	Uint32 previousFrameTicks = SDL_GetTicks();

	while (keepRunning)
	{
		//if (Collision::CircleCollision(sword.m_x + sword.m_width / 2, sword.m_y + sword.m_height / 2, sword.m_width / 2,
		//	door.m_x + door.m_width / 2, door.m_y + door.m_height / 2, door.m_width / 2)) {
		//	std::cout << "Sword and door are overlapping!" << std::endl;
		//}

		//if (Collision::BoundingBoxCollision(sword.m_x, sword.m_y, sword.m_width, sword.m_height, 
		//	door.m_x, door.m_y, door.m_width, door.m_height)) {
		//	std::cout << "Sword and door are overlapping!" << std::endl;
		//}

		//if (Collision::CircleCollision(sword.circleCollider, door.circleCollider)) {
		//	std::cout << "Sword and door are overlapping!" << std::endl;
		//}

		for (int i = 0; i < GameObject::gameObjects; i++)
		{
			for (int j = i + 1; j < GameObject::gameObjects; j++)
			{
				if (Collision::BoundingBoxCollision(gameObjectList[i].boxCollider, gameObjectList[j].boxCollider) && gameObjectList[i].isStatic && gameObjectList[j].isStatic) {
					std::cout << "Sword and door are overlapping!" << std::endl;
				}
			}
		}

		//if (Collision::BoundingBoxCollision(sword.boxCollider, door.boxCollider)) {
		//	std::cout << "Sword and door are overlapping!" << std::endl;
		//}

		Time::CalculateDeltaTime(previousFrameTicks);
		previousFrameTicks = SDL_GetTicks();

		float deltaTime = Time::GetDeltaTime();

		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			/*
			if (keyW) keyboardY -= movementSpeed;
			if (keyS) keyboardY += movementSpeed;
			if (keyA) keyboardX -= movementSpeed;
			if (keyD) keyboardX += movementSpeed;

			if (sdlEvent.type == SDL_QUIT) keepRunning = false;
			if (sdlEvent.type == SDL_KEYDOWN)
			{
				switch (sdlEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE: keepRunning = false; break;
				case SDLK_w: keyW = 1; break;
				case SDLK_s: keyS = 1; break;
				case SDLK_a: keyA = 1; break;
				case SDLK_d: keyD = 1; break;
				default: break;
				}
			}
			if (sdlEvent.type == SDL_KEYUP)
			{
				switch (sdlEvent.key.keysym.sym)
				{
					case SDLK_w: keyW = 0; break;
					case SDLK_s: keyS = 0; break;
					case SDLK_a: keyA = 0; break;
					case SDLK_d: keyD = 0; break;
					default: break;
				}
			}
			*/

			const Uint8* state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_W])
			{
				std::cout << "W was pressed!" << std::endl;
				sword.boxCollider.m_y -= movementSpeed * deltaTime;
				sword.circleCollider.m_y -= movementSpeed * deltaTime;

				
			}
			if (state[SDL_SCANCODE_S])
			{
				sword.boxCollider.m_y += movementSpeed * deltaTime;
				sword.circleCollider.m_y += movementSpeed * deltaTime;

				
			}
			if (state[SDL_SCANCODE_A])
			{
				sword.boxCollider.m_x -= movementSpeed * deltaTime;
				sword.circleCollider.m_x -= movementSpeed * deltaTime;

				
			}
			if (state[SDL_SCANCODE_D]) {
				sword.boxCollider.m_x += movementSpeed * deltaTime;
				sword.circleCollider.m_x += movementSpeed * deltaTime;

				
			}

			if (state[SDL_SCANCODE_UP]) {
				//door.m_y -= movementSpeed * deltaTime;
				g_cameraY -= movementSpeed * deltaTime;
			}
			if (state[SDL_SCANCODE_DOWN]) {
				//door.m_y += movementSpeed * deltaTime;
				g_cameraY += movementSpeed * deltaTime;
			}
			if (state[SDL_SCANCODE_LEFT]) {
				//door.m_x -= movementSpeed * deltaTime;
				g_cameraX -= movementSpeed * deltaTime;
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				//door.m_x += movementSpeed * deltaTime;
				g_cameraX += movementSpeed * deltaTime;
			}

			if (state[SDL_SCANCODE_SPACE]) {
				Mix_PlayChannel(-1, coinSFX, 0);

				sword.m_texture = doorTexture;
				Time::currentTimeScale = 0.5f;
			}
			
			if (state[SDL_SCANCODE_Z]) {
				Mix_PlayChannel(-1, coinSFX, 0);

				sword.m_texture = pngTexture;
				Time::currentTimeScale = 1.0f;
			}

			if (state[SDL_SCANCODE_X]) {
				factory.DestroyGameObject(sword);
			}

			if (state[SDL_SCANCODE_I]) {
				//textWidth *= g_zoomInOut;
				//textHeight *= g_zoomInOut;
				//AutoResizeTextWidthAndHeight(text, textWidth, textHeight);
				door.ZoomIn(g_zoomInOut);
				sword.ZoomIn(g_zoomInOut);
			}
			if (state[SDL_SCANCODE_O]) {
				//textWidth /= g_zoomInOut;
				//textHeight /= g_zoomInOut;
				//AutoResizeTextWidthAndHeight(text, textWidth, textHeight);
				door.ZoomOut(g_zoomInOut);
				sword.ZoomOut(g_zoomInOut);
			}

			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				keepRunning = false;
				break;
				/*
				case SDL_KEYDOWN:
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						keepRunning = false;
					}
					// ONLY UP
					else if (sdlEvent.key.keysym.sym == SDLK_w)
					{
						keyW = 1;
					}
					// ONLY DOWN
					else if (sdlEvent.key.keysym.sym == SDLK_s)
					{
						keyS = 1;
					}
					// ONLY LEFT
					else if (sdlEvent.key.keysym.sym == SDLK_a)
					{
						keyA = 1;
					}
					// ONLY RIGHT
					else if (sdlEvent.key.keysym.sym == SDLK_d)
					{
						keyD = 1;
					}
					break;
				case SDL_KEYUP:
					// ONLY UP
					if (sdlEvent.key.keysym.sym == SDLK_w)
					{
						keyW = 0;
					}
					// ONLY DOWN
					else if (sdlEvent.key.keysym.sym == SDLK_s)
					{
						keyS = 0;
					}
					// ONLY LEFT
					else if (sdlEvent.key.keysym.sym == SDLK_a)
					{
						keyA = 0;
					}
					// ONLY RIGHT
					else if (sdlEvent.key.keysym.sym == SDLK_d)
					{
						keyD = 0;
					}
					break;
				*/
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
		SDL_Rect destinationRect{ arrowX, arrowY, 32, 32 };
		SDL_Rect destinationRect2{ keyboardX, keyboardY, 40, 40 };
		SDL_Rect destinationRect3{ mouseX - 16, mouseY - 16, 32, 32 };

		// TODO: Font Rect
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDstRect);

		// TODO: Copy the texture onto the rendering target
		//SDL_RenderCopy(g_sdlRenderer, doorTexture, NULL, &destinationRect);
		//SDL_RenderCopy(g_sdlRenderer, crusaderTexture, NULL, &destinationRect2);
		//SDL_RenderCopy(g_sdlRenderer, pngTexture, NULL, &destinationRect2);
		door.Draw(g_sdlRenderer, g_cameraX, g_cameraY);
		sword.Draw(g_sdlRenderer, g_cameraX, g_cameraY);
		SDL_RenderCopy(g_sdlRenderer, textureWithoutSurface, NULL, &destinationRect3);

		// TODO: Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);

		gameObjectList.clear();
		gameObjectList.push_back(sword);
		gameObjectList.push_back(door);

		// TODO: Halt execution for 16 milliseconds (approx. 60 frames per second)
		SDL_Delay(16);
	}

	SDL_DestroyTexture(pngTexture);
	SDL_DestroyTexture(textureWithoutSurface);
	Mix_FreeChunk(coinSFX);
	Mix_FreeMusic(music);
	SDL_DestroyTexture(textTexture);

	CleanUp();

	return 0;
}