#pragma once
#include "Color.h"

class Material
{
private:
	float m_kd; // wspolczynnik diffuse
	float m_ks; //wspolczynnik specular
	float m_kg;
	Color *m_color;

public:




	Material();
	Material(Color &albedo, float d, float s);
	~Material();
	Color getColor() { return *m_color; }

	float getD() { return m_kd; }
	float getS() { return m_kd; }
	float getG() { return m_kd; }
	//Color getColor() { return *m_color; }

	static Material DBLUE_D;
	static Material RED_D;


};
