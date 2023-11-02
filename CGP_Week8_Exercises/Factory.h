#pragma once
#include "GameObject.h"

class Factory
{
public:
	GameObject CreateGameObject(SDL_Texture* texture, bool IsStatic);
	int DestroyGameObject(GameObject object);
};

