#pragma once
#include "SDL.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

class GameObject
{
public:
	static int gameObjects;

	GameObject(SDL_Texture* texture, bool IsStatic);

	BoxCollider boxCollider;
	CircleCollider circleCollider;

	bool isStatic;

	SDL_Texture* m_texture = nullptr;

	void Draw(SDL_Renderer* renderer, int cameraX, int cameraY);
	void ZoomIn(int zoomIn);
	void ZoomOut(int ZoomOut);
};

