#pragma once
#include "structures.h"
//#include "Image.h"


inline float uRand() {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

#pragma region regionFloat2
float float2::GetX(){	return m_x;}
float float2::GetY(){	return m_y;}

void float2::SetX(float x) { m_x = x; }
void float2::SetY(float y) { m_y = y; }

float2::float2(float x, float y) : m_x(x), m_y(y) {}
float2::float2() : m_x(0), m_y(0) {}
float2::~float2() {}

float float2::TriangleArea(float2 c, float2 b)
{
	float x1 = c.GetX() - m_x;
	float y1 = c.GetY() - m_y;
	float x2 = b.GetX() - m_x;
	float y2 = b.GetY() - m_y;
	return (x1 * y2 - x2 * y1);
}

inline float float2::length() { return sqrt(m_x * m_x + m_y * m_y); }

float2 float2::operator+ (float2 & o) { return float2(GetX() + o.GetX(), GetY() + o.GetY()); }
float2 float2::operator* (float2 & o) { return float2(GetX()*o.GetX(), GetY()*o.GetY()); }
float2 float2::operator- (float2 & o) { return float2(GetX() - o.GetY(), GetY() - o.GetX()); }
float2 float2::operator*(const float & o) { return float2(GetX() * o, GetY()*o); }

ostream& operator<<(ostream& str, float2& o) { return str << o.GetX() << ", " << o.GetY() << ", "; }
//ostream& operator<<(ostream& str, Color& o) { return str << o.getR() << ", " << o.getG() << ", " << o.getB(); }

#pragma endregion 

#pragma region regionFloat3


float3::float3() {}
float3::float3(float x, float y, float z) : x(x), y(y), z(z) {}
float3::float3(float3 p1, float3 p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}
float3::float3(float x, float y, float z, float l) : x(x), y(y), z(z) {	unitise();}
float3::~float3() {}

//odleglosc miedzy wektorami
float float3::distance(float3 a, float3 b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)); }

void float3::normalize()
{
	float l = length();
	if (x / l > eps5) x /= l; else x = 0;
	if (y / l > eps5) y /= l; else y = 0;
	if (z / l > eps5) z /= l; else z = 0;
}

//iloczyn skalarny
float float3::dot(float3 a, float3 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z); }

//iloczyn wektorowy
float3 float3::cross(float3 a, float3 b) {
	float3 v (
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
	//v.unitise();
	return v;
}

float float3::length() { return sqrt(x*x + y*y + z*z); }
void float3::unitise() {
	float nl = 1 / sqrt(x*x + y*y + z*z);
	x *= nl;  y *= nl;  z *= nl;
}


float3 float3::lerp(float3 a, float t){
	return float3(
		x + (a.x*t),
		y + (a.y*t),
		z + (a.z*t)
		);
}

float3 float3::operator+ (float3 const& o) { return float3(x + o.x, y + o.y, z + o.z); }
float3 float3::operator- (float3 const& o) { return float3(x - o.x, y - o.y, z - o.z); }
float3 float3::operator- () { return float3(-x, -y, -z); }
float3 float3::operator* (float const& o) { return float3(x*o, y*o, z*o); }
float3 float3::operator* (float3 const& o) { return float3(x*o.x, y*o.y, z*o.z); }
float3 float3::operator/ (float const& o) { return float3(x / o, y / o, z / o); }
float3 float3::operator/ (float3 const& o) { return float3(x / o.x,  y / o.y, z / o.z); }
void float3::operator+= (float3 const& o) { x += o.x; y += o.y; z += o.z; }
void float3::operator-= (float3 const& o) { x -= o.x; y -= o.y; z -= o.z; }
void float3::operator*= (float3 const& o) { x *= o.x; y *= o.y; z *= o.z; }
void float3::operator/= (float3 const& o) { x /= o.x; y /= o.y; z /= o.z; }
bool float3::operator== (float3 const& o)
{ 
	if (x == o.x && y == o.y && z == o.z) return true;
	else return false;
 }


ostream& operator<<(ostream& str, float3& o) { return str << o.x << ", " << o.y << ", " << o.z; }
//float3 operator- (float3 &o) { return float3(-o.x, -o.y, -o.y); }
//float3 operator+ (float3 &o) { return float3(o.x, o.y, o.y); }

#pragma endregion 
