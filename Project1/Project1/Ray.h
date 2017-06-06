#pragma once
#include "float3.h"
//#include "Sphere.h"
//#include "Plane.h"


class Ray
{
public:
	Ray();
	Ray(float3 origin, float3 direction);
	~Ray() {};
	float3 getOrigin() { return m_origin; }
	float3 getDirection() { return m_direction; }
	float getDistance() { return distance; }

private:
	float3 m_origin, m_direction, m_negdirection;// destination;
	float distance;
};