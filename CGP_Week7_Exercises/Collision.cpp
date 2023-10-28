#include "Collision.h"
#include <math.h>

bool Collision::CircleCollision(CircleCollider CC, CircleCollider otherCC)
{
	float dx = CC.m_x - otherCC.m_x;
	float dy = CC.m_y - otherCC.m_y;

	float distance = sqrt((dx * dx) + (dy * dy));

	if (distance < CC.m_radius + CC.m_radius) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::BoundingBoxCollision(BoxCollider BC, BoxCollider otherBC)
{
	if (BC.m_x + BC.m_width > otherBC.m_x && BC.m_x < otherBC.m_x + otherBC.m_width && 
		BC.m_y + BC.m_height > otherBC.m_y && BC.m_y < otherBC.m_y + otherBC.m_height) return true;
	else return false;
}
