#include "Sphere.h"




Sphere::Sphere()
{
}

Sphere::Sphere(float3 center, float radius) : center(center), radius(radius) {}

float3 Sphere::getNormal(float3& position) {
	float3 ret = position - center;
	ret.normalize();
	return ret;
	//  return ((position - center) * inverseRadius);
}
