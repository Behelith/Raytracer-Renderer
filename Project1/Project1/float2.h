#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class float2
{
	float m_x, m_y;
public:

	float GetX();
	float GetY();


	void SetX(float x);
	void SetY(float y);

	float2(float x, float y);
	float2();
	~float2();
	float dot(float2 b);

	void normalize();

	//float2 rotate(float angle);
	//float TriangleArea(float2 c, float2 b);


	//static float distance(float2 a, float2 b);
	//static float dot(float2 a, float2 b);


	inline float length();

	friend	ostream& operator<< (ostream&, float2&);

	float2 operator+ (float2 & o);
	float2 operator* (float2 & o);
	float2 operator- (float2 & o);
	float2 operator* (const float& o);

};

