#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(float3 center, float radius, Material &material);
	~Sphere() {};

	float3 getNormal(float3 & position);
	float3 getCenter() { return center; }
	float getRadius() { return radius; }
	void setCenter(float3 newCenter){		center = newCenter;	}
    HitInfo Intersect(Ray &ray, float distance);

private:
	float3 center;
	float radius;
};
	