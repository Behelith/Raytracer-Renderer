#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class float3
{
public:
	float x, y, z;

	float3();
	float3(float x, float y, float z);
	float3(float3 p1, float3 p2);
	float3(float x, float y, float z, float l);

	//float3(float3 v);
	~float3();

	static float distance(float3 a, float3 b);
	static float dot(float3 a, float3 b);
	static float3 cross(float3 a, float3 b);
	float3 lerp(float3 a, float t);

	void normalize();
	inline void unitise();

	float3 uChangeSpace(float3 Ex, float3 Ey, float3 Ez)
	{
		float3 v(
			x*Ex.x + y*Ey.x + z*Ez.z,
			x*Ex.y + y*Ey.y + z*Ez.y,
			x*Ex.z + y*Ey.z + z*Ez.z
		);
		v.unitise(); //!
		return v;
	}

	float3 rotate(float3 axis, float angle);

	float length();

	static float length(float3 a, float3 b)
	{
		float3 t = a - b;
		return sqrt(t.x*t.x + t.y*t.y + t.z*t.z);

	}

	float area(float3 v1, float3 v2, float3 v3) {
		float a = length(v2, v1);
		float b = length(v3, v1);
		float c = length(v3, v2);
		float p = (a + b + c) / 2.0f;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}

	friend	ostream& operator<< (ostream&, float3&);			//!!
	float3 operator+ (float3 const& o);
	float3 operator- (float3 const& o);
	float3 operator- ();						//przeksztalcenie wektora na odwrotny
	float3 operator* (float const& o);
	float3 operator* (float3 const& o);
	float3 operator/ (float const& o);
	float3 operator/ (float3 const& o);
	void operator+= (float3 const& o);
	void operator-= (float3 const& o);
	void operator*= (float3 const& o);
	void operator/= (float3 const& o);
	bool operator== (float3 const& o);

};

