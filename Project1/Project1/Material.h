#pragma once
#include "Color.h"

class Material
{
public:
	Color m_dr;
	Color m_sr;
	Color m_st;
	float ior;

	bool isDiffuse;       // czy materia³ odbija z rozproszeniem
	bool isSpecular;      // czy materia³ odbija zwierciadlanie
	bool isTransmittive;  // czy materia³ transmituje
	bool hasTextures;     // czy materia³ posiada tekstury
	bool hasDrMap;        // czy materia³ posiada mapê odbicia rozproszonego
	bool hasNormalMap;

	Material();
	Material(Color diffuse, Color specular, Color transmitance, float refraction);
	Material(Color diffuse, Color specular);
	~Material();

private:

};
