#pragma once
#include "structures.h"
#include "Sphere.h"
#include "Plane.h"


class Ray
{
public:
	Ray();
	Ray(float3 origin, float3 direction);
	~Ray() {};
	float3 getOrigin() { return m_origin; }
	float3 getDirection() { return m_direction; }
	float getDistance() { return distance; }

	float intersect(Sphere &sphere, float distance);
	float intersect(Plane &plane, float distance);


private:
	float3 m_origin, m_direction, m_negdirection;// destination;
	float distance;
};