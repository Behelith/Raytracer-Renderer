#include "float3.h"



float3::float3() : x(0), y(0), z(0) {}
float3::float3(float x, float y, float z) : x(x), y(y), z(z) {}
float3::float3(float3 p1, float3 p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}
float3::float3(float x, float y, float z, float l) : x(x), y(y), z(z) { normalize(); }
float3::~float3() {}

//odleglosc miedzy wektorami
float float3::distance(float3 a, float3 b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)); }

//iloczyn skalarny
float float3::dot(float3 a, float3 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z); }

//iloczyn wektorowy
float3 float3::cross(float3 a, float3 b) {
	float3 v(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
	//v.unitise();
	return v;
}

float float3::length() { return sqrt(x*x + y*y + z*z); }
void float3::normalize() {
	float nl = 1 / length();// sqrt(x*x + y*y + z*z);
	x *= nl;
	y *= nl;
	z *= nl;
}


float3 float3::lerp(float3 a, float t) {
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
float3 float3::operator/ (float3 const& o) { return float3(x / o.x, y / o.y, z / o.z); }
void float3::operator+= (float3 const& o) { x += o.x; y += o.y; z += o.z; }
void float3::operator-= (float3 const& o) { x -= o.x; y -= o.y; z -= o.z; }
void float3::operator*= (float3 const& o) { x *= o.x; y *= o.y; z *= o.z; }
void float3::operator/= (float3 const& o) { x /= o.x; y /= o.y; z /= o.z; }
bool float3::operator==(float3 const& o)
{
	if (x == o.x && y == o.y && z == o.z) return true;
	return false;
}

ostream& operator<<(ostream& str, float3& o) { return str << o.x << ", " << o.y << ", " << o.z; }

float3 float3::rotate(float3 axis, float angle)
{
	float sinAngle = sin(-angle);
	float cosAngle = cos(-angle);

	//	float3 c = axis * sinAngle;
	float3 cur(x, y, z);
	return cross(cur, axis * sinAngle + (           //Rotation on local X
		(cur * cosAngle) + (						 //Rotation on local Z
			axis * dot(cur, axis *(1 - cosAngle))))); //Rotation on local Y

}

