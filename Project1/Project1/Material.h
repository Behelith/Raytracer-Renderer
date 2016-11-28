#pragma once
#include "Color.h"
#include "Texture.h"

class Material
{
private:
	float m_kd; // wspolczynnik diffuse
	float m_ks; //wspolczynnik specular
	float m_kc;
	float m_ka;
	Color m_color;
	Texture m_texture; // textura;
	bool isTextured = false;

public:
	Material();
	Material(Color albedo, float d, float s);
	Material(const char * filename, float d, float s);
	Material(Color albedo, float d, float s, float a, unsigned int c);
	~Material();
	Color getColor() { return m_color; }

	float getD() { return m_kd; }
	float getS() { return m_ks; }
	float getC() { return m_kc; }
	float getA() { return m_ka; }

	bool getIsTextured() { return isTextured; }
	//Color getColor() { return *m_color; }

	static Material DBLUE_D;
	static Material TEX_1;
	static Material WHITE_S;
	static Material RED_D;
	static Material ORANGE;
	static Material ORANGE_S;
	static Material YELLOW;
	static Material YELLOW_D;
	static Material GRAY;
	static Material DGRAY;
	static Material GREEN;


};
