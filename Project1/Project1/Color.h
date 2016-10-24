#pragma once

class Color
{
private:
	float m_r, m_g, m_b, m_a;

public:
	//unsigned int m_color;

	//!!!! jak trzymac kolor, jako R,G,B <0,255>, <0,1>, czy hex 
	// poki co float

	Color(float r, float g, float b, float a);	//
	Color(float r, float g, float b);
	Color(int r, int g, int b);
	Color(unsigned int color);
	Color();

	float getR();
	float getG();
	float getB();
	float getA();

	bool isBlack();
	void cut();
	unsigned int toHex();

	Color operator+ (Color & a);
	void operator+= (Color & a);
	Color operator- (Color & a);
	void operator-= (Color & a);
	Color operator* (Color & a);
	Color operator* (float const& a);
	Color operator/ (float const& a);

	static int rToInt(unsigned int color);
	static int gToInt(unsigned int color);
	static int bToInt(unsigned int color);
	static int aToInt(unsigned int color);

};
