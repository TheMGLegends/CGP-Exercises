#pragma once
#include "SDL.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

class GameObject
{
public:
	static int gameObjects;

	bool isAnimated = false;
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1;
	bool isFlipped = false;

	GameObject(SDL_Texture* texture, bool IsStatic);

	BoxCollider boxCollider;
	CircleCollider circleCollider;

	bool isStatic;

	SDL_Texture* m_texture = nullptr;

	void Draw(SDL_Renderer* renderer, int cameraX, int cameraY);
	void ZoomIn(int zoomIn);
	void ZoomOut(int ZoomOut);
};

