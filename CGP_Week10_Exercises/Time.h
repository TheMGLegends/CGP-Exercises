#pragma once
#include "SDL.h"
class Time
{
public:
	static float deltaTime;
	static float currentTimeScale;
	static void CalculateDeltaTime(Uint32 previousFrameTicks);

	static float GetDeltaTime();
};

