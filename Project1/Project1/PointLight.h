#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(float3 position, Color color);
	PointLight(float3 position, Color color, float cA, float lA, float qA);
	PointLight();
	~PointLight();

};

