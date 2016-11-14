#include "Material.h"

Material::Material()
{
	m_color = Color::RED;
	m_kd = 0.5f;
	m_ks = 0.5f;
}

Material::~Material()
{
}

Material::Material(Color albedo, float d, float s)
{
	m_color = albedo;
	m_kd = d;
	m_ks = s;
	m_ka = 0.3f;
	m_kc = 8;
}


Material::Material(Color albedo, float d, float s, float a, unsigned int c)
{
	m_color = albedo;
	m_kd = d;
	m_ks = s;
	m_ka = a;
	m_kc = c;
}

//Material Material::NAZWA = Material( KOLOR, kd, ks);

Material Material::DBLUE_D = Material(Color::BLUE, 0.8f, 0.1f);
Material Material::RED_D = Material(Color::RED, 0.8f, 0.1f);
Material Material::ORANGE = Material(Color::ORANGE, 0.8f, 0.1f);
Material Material::YELLOW = Material(Color::YELLOW, 0.8f, 0.1f);
Material Material::YELLOW_D = Material(Color::YELLOW, 0.5f, 0.8f, 0.08f, 32);
Material Material::ORANGE_S = Material(Color(0.9f, 0.3f, 0.f ), 0.5f, 0.8f, 0.08f, 32);
Material Material::GREEN = Material(Color::GREEN, 0.8f, 0.1f);
Material Material::GRAY = Material(Color::GRAY, 0.8f, 0.1f);
Material Material::DGRAY = Material(Color::DGRAY , 0.8f, 0.1f);
