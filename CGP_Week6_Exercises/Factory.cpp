#include "Factory.h"

GameObject Factory::CreateGameObject(SDL_Texture* texture)
{
	return GameObject{ texture };
}

int Factory::DestroyGameObject(GameObject object)
{
	SDL_DestroyTexture(object.m_texture);
	return 0;
}
