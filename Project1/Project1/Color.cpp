#include "Color.h"
#include <complex.h>
#include <valarray>
#include <iostream>


/*
Color::Color(short r, short g, short b, short a) : m_color(r << 24 | g << 16 | b << 8 | a ){}
Color::Color(short r, short g, short b) : m_color(r << 24 | g << 16 | b << 8 | 255) {}
Color::Color(unsigned int color) : m_color(color){}
Color::Color() : m_color(0x000000ff) {}
*/


/*Color::Color(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {}
Color::Color(short r, short g, short b) : r(r), g(g), b(b), a(255) {}*/

Color::Color(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}
Color::Color(float r, float g, float b) : m_r(r), m_g(g), m_b(b), m_a(1) {}
Color::Color(int r, int g, int b) : m_r(float(r) / 255), m_g(float(g) / 255), m_b(float(b) / 255), m_a(1) {}

Color::Color(unsigned int color) :
	m_r(float(Color::rToInt(color)) / 255),
	m_g(float(Color::gToInt(color)) / 255),
	m_b(float(Color::bToInt(color)) / 255),
	m_a(float(Color::aToInt(color)) / 255)
{}

Color::Color() : m_r(0.0f), m_g(.0f), m_b(.0f), m_a(1.0f) {}

float Color::getR() { return m_r; }
float Color::getG() { return m_g; }
float Color::getB() { return m_b; }
float Color::getA() { return m_a; }

bool Color::isBlack()
{
	return (m_r == m_b == m_g == 0) ? true : false;
}

unsigned int Color::toHex()
{
	int r = (int)(m_r * 255);
	int g = (int)(m_g * 255);
	int b = (int)(m_b * 255);
	int a = (int)(m_a * 255);

	return (r << 24 | g << 16 | b << 8 | a);
}

int Color::rToInt(unsigned int color) { return (color >> 24) & 0xff; }
int Color::gToInt(unsigned int color) { return (color >> 16) & 0xff; }
int Color::bToInt(unsigned int color) { return (color >> 8) & 0xff; }
int Color::aToInt(unsigned int color) { return (color)& 0xff; }

bool Color::IsSimilar(Color b, float epsilon)
{
	//*
	if (
		std::abs(getR() - b.getR()) >= epsilon ||
		std::abs(getG() - b.getG()) >= epsilon ||
		std::abs(getB() - b.getB()) >= epsilon
		)

		return false;
		else return true;
}

Color Color::operator+ (Color & o) { return Color(m_r + o.getR(), m_g + o.getG(), m_b + o.getB(), m_a + o.getA()); }
void Color::operator+= (Color & o) { m_r = m_r + o.getR(); m_g = m_g + o.getG(); m_b = m_b + o.getB(); m_a = m_a + o.getA(); }
Color Color::operator- (Color & o) { return Color(m_r - o.getR(), m_g - o.getG(), m_b - o.getB(), m_a - o.getA()); }
void Color::operator-= (Color & o) { m_r = m_r - o.getR(); m_g = m_g - o.getG(); m_b = m_b - o.getB(); m_a = m_a - o.getA(); }
Color Color::operator* (Color & o) { return Color(m_r * o.getR(), m_g * o.getG(), m_b * o.getB(), m_a * o.getA()); }
Color Color::operator* (float const& o) { return Color(m_r * o, m_g * o, m_b * o, m_a * o); }
Color Color::operator/ (float const& o) { return Color(m_r / o, m_g / o, m_b / o, m_a / o); }
