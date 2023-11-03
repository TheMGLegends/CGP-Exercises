#pragma once
#include "BoxCollider.h"
#include "CircleCollider.h"

class Collision
{
public:
	static bool CircleCollision(CircleCollider CC, CircleCollider otherCC);
	static bool BoundingBoxCollision(BoxCollider BC, BoxCollider otherBC);
};

