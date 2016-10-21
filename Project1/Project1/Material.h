#pragma once
#include "Color.h"

class Material
{
public:
	Color m_dr;
	Color m_sr;
	Color m_st;
	float ior;

	bool isDiffuse;       // czy materia� odbija z rozproszeniem
	bool isSpecular;      // czy materia� odbija zwierciadlanie
	bool isTransmittive;  // czy materia� transmituje
	bool hasTextures;     // czy materia� posiada tekstury
	bool hasDrMap;        // czy materia� posiada map� odbicia rozproszonego
	bool hasNormalMap;

	Material();
	Material(Color diffuse, Color specular, Color transmitance, float refraction);
	Material(Color diffuse, Color specular);
	~Material();

private:

};
