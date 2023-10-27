#pragma once
#include "SDL.h"

class GameObject
{
public:
	GameObject(SDL_Texture* texture);

	int m_x = 0;
	int m_y = 0;
	int m_width = 100;
	int m_height = 100;
	SDL_Texture* m_texture = nullptr;

	void Draw(SDL_Renderer* renderer);
};

