#include "GameObject.h"

int GameObject::gameObjects = 0;

GameObject::GameObject(SDL_Texture* texture, bool IsStatic)
{
	m_texture = texture;
	isStatic = IsStatic;
	gameObjects++;
}

void GameObject::Draw(SDL_Renderer* renderer, int cameraX, int cameraY)
{
	SDL_Rect destinationRect{ boxCollider.m_x - cameraX, boxCollider.m_y - cameraY, boxCollider.m_width, boxCollider.m_height };
	SDL_RenderCopy(renderer, m_texture, NULL, &destinationRect);
}

void GameObject::ZoomIn(int zoomIn)
{
	boxCollider.m_x += boxCollider.m_width * zoomIn;
	boxCollider.m_y += boxCollider.m_height * zoomIn;

	boxCollider.m_width *= zoomIn;
	boxCollider.m_height *= zoomIn;
}

void GameObject::ZoomOut(int zoomOut)
{
	boxCollider.m_x -= boxCollider.m_width / zoomOut;
	boxCollider.m_y -= boxCollider.m_height / zoomOut;

	boxCollider.m_width /= zoomOut;
	boxCollider.m_height /= zoomOut;
}
