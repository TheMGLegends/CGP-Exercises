#include "GameObject.h"

int GameObject::gameObjects = 0;

GameObject::GameObject(SDL_Texture* texture, bool IsStatic)
{
	m_texture = texture;
	isStatic = IsStatic;
	gameObjects++;
}

void GameObject::Draw(SDL_Renderer* renderer)
{
	SDL_Rect destinationRect{ boxCollider.m_x, boxCollider.m_y, boxCollider.m_width, boxCollider.m_height };
	SDL_RenderCopy(renderer, m_texture, NULL, &destinationRect);
}
