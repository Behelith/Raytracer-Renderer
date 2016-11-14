#pragma once
#include "Color.h"

class Material
{
private:
	float m_kd; // wspolczynnik diffuse
	float m_ks; //wspolczynnik specular
	float m_kc;
	float m_ka;
	Color m_color;

public:
	Material();
	Material(Color albedo, float d, float s);
	Material(Color albedo, float d, float s, float a, unsigned int c);
	~Material();
	Color getColor() { return m_color; }

	float getD() { return m_kd; }
	float getS() { return m_ks; }
	float getC() { return m_kc; }
	float getA() { return m_ka; }
	//Color getColor() { return *m_color; }

	static Material DBLUE_D;
	static Material RED_D;
	static Material ORANGE;
	static Material ORANGE_S;
	static Material YELLOW;
	static Material YELLOW_D;
	static Material GRAY;
	static Material DGRAY;
	static Material GREEN;


};
