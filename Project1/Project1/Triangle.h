#pragma once
#include "structures.h"
class Triangle
{
public:
	float3 m_verts[3];
	Triangle();
	Triangle(float3 a, float3 b, float3 c);
	~Triangle(); 
};

