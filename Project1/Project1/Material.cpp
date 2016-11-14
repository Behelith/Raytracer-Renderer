#include "Material.h"

Material::Material()
{
	m_color = &Color::RED;
	m_kd = 0.5f;
	m_ks = 0.5f;
}

Material::~Material()
{
}

Material::Material(Color &albedo, float d, float s)
{
	m_color = &albedo;
	m_kd = d;
	m_ks = s;
}


//Material Material::NAZWA = Material( KOLOR, kd, ks);

Material Material::DBLUE_D = Material(Color::BLUE, 0.8f, 0.1f);
Material Material::RED_D = Material(Color::RED, 0.8f, 0.1f);
Material Material::ORANGE = Material(Color::ORANGE, 0.8f, 0.1f);
Material Material::YELLOW = Material(Color::YELLOW, 0.8f, 0.1f);
Material Material::GREEN = Material(Color::GREEN, 0.8f, 0.1f);
Material Material::GRAY = Material(Color::GRAY, 0.8f, 0.1f);
Material Material::DGRAY = Material(Color::DGRAY , 0.8f, 0.1f);
