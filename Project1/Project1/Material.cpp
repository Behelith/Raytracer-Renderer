#include "Material.h"

Material::Material(Color diffuse, Color specular, Color transmitance, float refraction)
	: m_dr(diffuse),
	m_sr(specular),
	m_st(transmitance),
	ior(refraction) {}

Material::Material(Color diffuse, Color specular) :
	m_dr(diffuse), m_sr(specular) {}
