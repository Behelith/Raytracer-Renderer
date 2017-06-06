#include "float2.h"
#include "structures.h"


float float2::GetX() { return m_x; }

float float2::GetY() { return m_y; }

void float2::SetX(float x) { m_x = x; }

void float2::SetY(float y) { m_y = y; }

float2::float2(float x, float y) : m_x(x), m_y(y) {}

float2::float2() : m_x(0), m_y(0) {}

float2::~float2() {}

float float2::dot(float2 b)
{
	return m_x * b.GetX() + m_y * b.GetX();
}

void float2::normalize()
{
	float nl = 1 / length();
	m_x *= nl;
	m_y *= nl;
}

//float2 float2::rotate(float angle)
//{
//	float rad = angle*PI180;
//	float rcos = cos(rad);
//	float rsin = sin(rad);
//
//	return float2(m_x * rcos - m_y * rsin, m_x * rsin + m_y *rcos);
//}
//
//float float2::TriangleArea(float2 c, float2 b)
//{
//	float x1 = c.GetX() - m_x;
//	float y1 = c.GetY() - m_y;
//	float x2 = b.GetX() - m_x;
//	float y2 = b.GetY() - m_y;
//
//	return (x1 * y2 - x2 * y1)*0.5;
//}

inline float float2::length() { return sqrt(m_x * m_x + m_y * m_y); }

float2 float2::operator+ (float2 & o) { return float2(GetX() + o.GetX(), GetY() + o.GetY()); }

float2 float2::operator* (float2 & o) { return float2(GetX()*o.GetX(), GetY()*o.GetY()); }

float2 float2::operator- (float2 & o) { return float2(GetX() - o.GetY(), GetY() - o.GetX()); }

float2 float2::operator*(const float & o) { return float2(GetX() * o, GetY()*o); }

ostream& operator<<(ostream& str, float2& o) {
	return str << o.GetX() << ", " << o.GetY() << ", ";
}