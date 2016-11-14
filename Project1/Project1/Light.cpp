#include "Light.h"



Light::Light()
{
	m_lightType = -1;
	m_color = Color::BLACK;
	m_position = float3(0, 0, 0);

	m_constAtt = 1.f;
	m_linearAtt = 1.f;
	m_quadAtt = 1.f;
}

Light::Light(float3 position, Color &color)
{
	m_lightType = 0;
	m_color = color;
	m_position = position;

	m_constAtt = 1.f;
	m_linearAtt = 1.f;
	m_quadAtt = 1.f;
}

Light::~Light()
{
//	delete m_color;
}
