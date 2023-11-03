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
	SDL_Rect srcRect;

	if (isAnimated) {
		int currentFrameIndex = (int)(timeInAnimationState * animationSpeed) % animFrames;
		srcRect = { currentFrameIndex * animPixelWidth, animState * animPixelHeight, animPixelWidth, animPixelHeight };
	}
	
	SDL_Rect destinationRect{ boxCollider.m_x - cameraX, boxCollider.m_y - cameraY, boxCollider.m_width, boxCollider.m_height };

	if (isFlipped) {
		SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
		SDL_RenderCopyEx(renderer, m_texture, isAnimated ? &srcRect : NULL, &destinationRect, 180, NULL, flip);
	}
	else {
		SDL_RenderCopy(renderer, m_texture, isAnimated ? &srcRect : NULL, &destinationRect);
	}

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
