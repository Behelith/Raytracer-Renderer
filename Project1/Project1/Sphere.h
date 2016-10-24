#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(float3 center, float radius);
	float3 getNormal(float3 & position);
	~Sphere() {};
	float3 getCenter() { return center; }
	float getRadius() { return radius; }
	Color getColor() { return *m_color; }
	void setCenter(float3 newCenter)
	{
		center = newCenter;
	}
private:
	float3 center;
	float radius;
};
