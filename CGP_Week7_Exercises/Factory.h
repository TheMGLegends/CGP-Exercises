#pragma once
#include "GameObject.h"

class Factory
{
public:
	GameObject CreateGameObject(SDL_Texture* texture);
	int DestroyGameObject(GameObject object);
};

