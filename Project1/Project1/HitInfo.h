#pragma once
#include "structures.h"
#include "Color.h"

class HitInfo
{
private:
	float3 m_normal;
	float3 m_point;
	Color m_color;
	float m_distance;
public:
	HitInfo();
	HitInfo(float3 normal, float3 point, Color color, float distance);
	float getDistance() { return m_distance; }
	float3 getPoint() { return m_point; }
	float3 getNormal() { return m_normal; }
	Color getColor() { return m_color; } // ??

	~HitInfo();
};

