#include "Light.h"



Light::Light()
{
	m_color = &Color::BLACK;
	m_position = float3(0, 0, 0);
}

Light::Light(float3 position, Color &color)
{
	m_color = &color;
	m_position = position;
}

Light::~Light()
{
}
