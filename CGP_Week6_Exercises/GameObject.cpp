#include "GameObject.h"

GameObject::GameObject(SDL_Texture* texture)
{
	m_texture = texture;
}

void GameObject::Draw(SDL_Renderer* renderer)
{
	SDL_Rect destinationRect{ m_x, m_y, m_width, m_height };
	SDL_RenderCopy(renderer, m_texture, NULL, &destinationRect);
}
