#include "Time.h"

float Time::currentTimeScale = 1.0f;
float Time::deltaTime = 0;

void Time::CalculateDeltaTime(Uint32 previousFrameTicks)
{
	deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
}

float Time::GetDeltaTime()
{
	return deltaTime * currentTimeScale;
}
