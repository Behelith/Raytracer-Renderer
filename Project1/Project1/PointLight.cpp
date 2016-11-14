#include "PointLight.h"

PointLight::PointLight(float3 position, Color color) {
	m_color = color;
	m_position = position;
	m_lightType = 1;
	m_constAtt = 0.02f;
	m_linearAtt = 0.05f;
	m_quadAtt = 0.05f;
}

PointLight::PointLight()
{
	m_color = Color::WHITE;
	m_position = float3(0.f,1.f,0.f);
	m_lightType = 1;
	m_constAtt = 5;
	m_linearAtt = 5;
	m_quadAtt = 5;
}

PointLight::PointLight(float3 position, Color color, float cA, float lA, float qA) {
	m_color = color;
	m_position = position;
	m_lightType = 1;
	m_constAtt = cA;
	m_linearAtt = lA;
	m_quadAtt = qA;
}


PointLight::~PointLight()
{
}

