#pragma once
#include <ostream>

using namespace std;
//
//Color
//c1(255, 200, 15),
//c2(255, 127, 40),
//c3(1.f, 0.f, 0.f),
//c4(.0f, 1.0f, 0.f),
//c5(.0f, 0.0f, 1.f),
//c6(1.0f, 0.0f, 1.f);



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
	//ostream& operator<<(ostream& str, float2& o) { return str << o.GetX() << ", " << o.GetY() << ", "; }
	friend ostream& operator<<(ostream&, Color& );
//	Color operator<< (float const& a);

	static int rToInt(unsigned int color);
	static int gToInt(unsigned int color);
	static int bToInt(unsigned int color);
	static int aToInt(unsigned int color);

	bool IsSimilar(Color b, float epsilon = 0);

	//const
	static Color BLACK;
	static Color WHITE;
	static Color GRAY;
	static Color DGRAY;
	static Color RED;
	static Color GREEN;
	static Color BLUE;
	static Color LVIOLET;
	static Color DVIOLET;
	static Color YELLOW;

	static Color ORANGE;
};
