#include "Factory.h"

GameObject Factory::CreateGameObject(SDL_Texture* texture, bool IsStatic)
{
	return GameObject{ texture, IsStatic };
}

int Factory::DestroyGameObject(GameObject object)
{
	SDL_DestroyTexture(object.m_texture);
	return 0;
}
