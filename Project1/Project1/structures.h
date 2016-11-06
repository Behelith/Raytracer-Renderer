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

static Color C1(1.f, 0.f, 0.f);
static Color C2(0.f, 1.f, 0.f);
static Color C3(0.f, 0.f, 1.f);
static Color C4(1.f, 1.f, 0.f);
static Color C5(0.f, 1.f, 1.f);
static Color C6(1.f, 0.f, 1.f);
static Color C7(133, 96, 168);
static Color C8(50, 0, 75);


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

