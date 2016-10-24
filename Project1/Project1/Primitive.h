#pragma once
#include "structures.h"
#include "Color.h"

class Primitive
{
public:
	Primitive();
	~Primitive();
	float3 getCenter() { return center; }
	virtual Color getColor() = 0;
	virtual void setColor(Color &color);
	
protected:
	float3 center;
	//unsigned int m_color;
	Color *m_color;
};

