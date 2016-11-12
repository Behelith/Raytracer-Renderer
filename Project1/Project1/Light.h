#pragma once
#include "structures.h"

class Light
{
private:
	float3 m_position;
	Color *m_color;
	
public:
	Light();
	Light(float3 position, Color &color);
	~Light();

//	float getG ()
};

