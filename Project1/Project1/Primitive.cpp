#include "Primitive.h"



Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

void Primitive::setColor(Color &color)
{
	m_color = &color;
}
