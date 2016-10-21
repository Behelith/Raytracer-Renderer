#pragma once
#include "structures.h"

class Plane
{
public:
	Plane();
	Plane(float3 normal, float distance);
	float3& getNormal();
	float getDistance();
	//int intersect(Ray& ray, float distance);
	//float3 getNormal(float3& a_Pos);
private:
	float3 m_normal;
	float m_distance;
};