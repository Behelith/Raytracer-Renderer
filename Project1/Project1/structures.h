#pragma once
#include <string>
#include <SDL.h>
#include <iostream>

#include <cmath>
#include <chrono>
#include <cstdlib>
#include <vector>
#include "Color.h"


//#include "Stars3D.h"


using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;
static float FOV = 100.0f;
#define getTime get_time::now();

static auto currentTime = get_time::now();
static auto previousTime = get_time::now();

static float getFOV() { return FOV; }
inline static int64_t getDelay()
{
	auto diff = currentTime - previousTime;
	int64_t tmp = chrono::duration_cast<ns>(diff).count();
	//cout << "Elapsed time is :  " << tmp << " ns " << endl;
	return tmp;
}

const float eps3 = 0.001f;
const float eps5 = 0.00001f;
const float UNDEFINED = INFINITY;
const float PI = 3.14159265f;
const float PIx2 = 6.28318530f;

//indeksy refrakcji
const float REFRACTION_VACUUM = 1.0000f;
const float REFRACTION_AIR = 1.0003f;
const float REFRACTION_ICE = 1.3100f;
const float REFRACTION_WATER = 1.3330f;
const float REFRACTION_GASOLINE = 1.3980f;
const float REFRACTION_GLASS = 1.5500f;
const float REFRACTION_SAPPHIRE = 1.7700f;
const float REFRACTION_DIAMOND = 2.4190f;

typedef unsigned int nat;

inline float uRand();

#pragma region regionFloat2

// punkt 2 wymiarowy
class float2
{

private:
	float m_x, m_y;
public:

	float GetX();
	float GetY();


	void SetX(float x);
	void SetY(float y);

	float2(float x, float y);
	float2();
	~float2();

	//static float distance(float2 a, float2 b);
	//static float dot(float2 a, float2 b);
	
	float TriangleArea(float2 c, float2 b);

	inline float length();

	friend	ostream& operator<< (ostream&, float2&);



	float2 operator+ (float2 & o);
	float2 operator* (float2 & o);
	float2 operator- (float2 & o);
	float2 operator* (const float& o);


};


#pragma endregion 

#pragma region regionFloat3
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

	float length();

	static float length (float3 a, float3 b)
	{
		float3 t = a - b;
		return sqrt(t.x*t.x + t.y*t.y + t.z*t.z);

	}

	 float area(float3 v1, float3 v2, float3 v3) {
		float a = length(v2 , v1);
		float b = length(v3 , v1);
		float c = length(v3 , v2);
		float p = (a + b + c) / 2.0f;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}

	friend	ostream& operator<< (ostream&, float3&);
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

private:
};


#pragma endregion 

#pragma region Regionfloat4

class float4
{
	float4()
	{

	}
};
#pragma endregion 

