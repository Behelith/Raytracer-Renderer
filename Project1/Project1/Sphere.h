#pragma once
#include "structures.h"

class Sphere
{
public:
	Sphere();
	Sphere(float3 center, float radius);
	float3 getNormal(float3 & position);
	~Sphere() {};
	float3 getCenter() { return center; }
	float getRadius() { return radius; }
private:
	float3 center;
	float radius;
};