#include "Material.h"
#include <SDL.h>
#include "structures.h"


Material::Material()
{
	//	m_texture = nullptr;
		m_color = Color::RED;
	m_kd = 0.5f;
	m_ks = 0.5f;
	m_krefl = 0.0f;
	m_krefr = 0.0f;
}

Material::~Material()
{
}

Material::Material(Color albedo, float d, float s)
{
//	m_texture = nullptr;
	m_color = albedo;
	m_kd = d;
	m_ks = s;
	m_ka = 0.3f;
	m_kc = 8;


//	m_refl = 0.0f;
//	m_refr = 0.0f;
	m_krefl = 0.0f;
	m_krefr = 0.0f;
}

Material::Material(const char * filename, float d, float s)
{
	m_texture = Texture(filename);
	isTextured = true;
	m_kd = d;
	m_ks = s;
	m_ka = 0.3f;
	m_kc = 8;

//	m_refl = 0.0f;
//	m_refr = 0.0f;
	m_krefl = 0.0f;
	m_krefr = 0.0f;
}

Material::Material(Color albedo, float d, float s, float a, unsigned int c)
{
	//m_texture = nullptr;
	m_color = albedo;
	m_kd = d;
	m_ks = s;
	m_ka = a;
	m_kc = c;
}

Material::Material(Color albedo, float d, float s, float a, unsigned int c, float refl, float refr, float krefl, float krefr)
{
	m_color = albedo;
	m_kd = d;
	m_ks = s;
	m_ka = a;
	m_kc = c;
	m_refl = refl;
	m_refr = refr;
	m_krefl = krefl;
	m_krefr = krefr;
}

//Material Material::NAZWA = Material( KOLOR, kd, ks);

Material Material::DBLUE_D = Material(Color::BLUE, 0.8f, 0.1f);
Material Material::RED_D = Material(Color::RED, 0.8f, 0.1f, 0.08f, 32);
//Material Material::TEX_1 = Material("render.png", 0.8f, 0.1f);
Material Material::ORANGE = Material(Color::ORANGE, 0.8f, 0.1f);
Material Material::YELLOW = Material(Color::YELLOW, 0.8f, 0.1f);
Material Material::YELLOW_D = Material(Color::YELLOW, 0.5f, 0.8f, 0.08f, 32);
Material Material::ORANGE_S = Material(Color(0.9f, 0.3f, 0.f), 0.5f, 0.8f, 0.08f, 32);
Material Material::WHITE_S = Material(Color(1.f, 1.f, 1.f ), 0.5f, 0.8f, 0.08f, 32);
Material Material::GREEN = Material(Color::GREEN, 0.8f, 0.1f);
Material Material::GRAY = Material(Color::GRAY, 0.8f, 0.1f);
Material Material::DGRAY = Material(Color::DGRAY , 0.8f, 0.1f);


Material Material::WHITE_SHINY = Material(Color::WHITE, 0.6f, 0.8f, 0.08f, 1024, 1.0f, 0.0f, 0.05f, 0.0f);

Material Material::MIRROR = Material(Color::WHITE, 0.05f, 0.5f, 0.08f, 128, 1.0f, 0.0f, 0.85f, 0.0f);
Material Material::GLASS = Material(Color::GRAY, 0.05f, 0.5f, 0.08f, 128, 1.0f, REFRACTION_GLASS, 0.08f, 0.8f);
