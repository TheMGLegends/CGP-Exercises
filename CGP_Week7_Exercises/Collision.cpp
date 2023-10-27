#include "Collision.h"
#include <math.h>

bool Collision::CircleCollision(float c1X, float c1Y, float r1, float c2X, float c2Y, float r2)
{
	float dx = c2X - c1X;
	float dy = c2Y - c1Y;

	float distance = sqrt((dx * dx) + (dy * dy));

	if (distance < r1 + r2) {
		return true;
	}
	else {
		return false;
	}
}
