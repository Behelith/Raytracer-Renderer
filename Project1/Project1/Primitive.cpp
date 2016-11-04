#include "Primitive.h"



Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

Color Primitive::getColor() { return *m_color; }


float Primitive::Intersect(Ray& ray, float distance)
{
	return -1;
}

void Primitive::setColor(Color &color)
{
	m_color = &color;
}
