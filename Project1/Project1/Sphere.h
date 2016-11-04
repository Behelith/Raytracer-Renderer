#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(float3 center, float radius, Color &color);
	~Sphere() {};

	float3 getNormal(float3 & position);
	float3 getCenter() { return center; }
	float getRadius() { return radius; }
	void setCenter(float3 newCenter){		center = newCenter;	}
    float Intersect(Ray &ray, float distance);

private:
	float3 center;
	float radius;
};
	