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

	float m_krefl = 0.0f;
	float m_krefr = 0.0f;
	
	float m_refl = 0.0;
	float m_refr = 0.0;

	Color m_color;

	Texture m_texture; // textura;
	bool isTextured = false;

public:
	Material();
	Material(Color albedo, float d, float s);
	Material(const char * filename, float d, float s);
	Material(Color albedo, float d, float s, float a, unsigned int c);


	Material(Color albedo, float d, float s, float a, unsigned int c, float refl, float refr, float krefl, float krefr);

	~Material();
	Color getColor() { return m_color; }

	float getKRefl() { return m_krefl; }
	float getKRefr() { return m_krefr; }	
	float getReflectivity() { return m_refl; }
	float getRefraction() { return m_refr; }
	float getD() { return m_kd; }
	float getS() { return m_ks; }
	float getC() { return m_kc; }
	float getA() { return m_ka; }

	bool getIsTextured() { return isTextured; }
	Texture getTexture() { return m_texture; }
	void setTexture(Texture texture) { m_texture = texture; isTextured = true; }
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
	static Material WHITE_D;

	static Material DGREEN_MATT;
	static Material DGREEN_GLOSS;
	static Material SKYBLUE_MATT;
	static Material SKYBLUE_GLOSS;
	static Material PINK_MATT;
	static Material PINK_GLOSS;
	static Material LVIOLET_MATT;
	static Material LVIOLET_GLOSS;
	static Material DBLUE_MATT;
	static Material DBLUE_GLOSS;
	static Material RED_MATT;
	static Material RED_GLOSS;
	static Material YELLOW_MATT;
	static Material YELLOW_GLOSS;

	static Material WHITE_SHINY;

	static Material MIRROR;
	static Material GLASS;





};
