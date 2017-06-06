#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

class float4
{
	

public:
	float m_x;
	float m_y;
	float m_z;
	float m_w;

	float4()
	{
		m_x = 0;
		m_y = 0;
		m_z = 0;
		m_w = 0;
	}

	float4(float x, float y, float z, float w)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	float Length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	float Max()
	{
		return max(max(m_x, m_y), max(m_z, m_w));
	}


	float dot( float4 r)
	{
		//return a.GetX() * r.GetX() + a.GetY() * r.GetY() + a.GetZ() * r.GetZ() + a.GetW() * r.GetW();
		return GetX() * r.GetX() + GetY() * r.GetY() + GetZ() * r.GetZ() + GetW() * r.GetW();

	}

	float4 cross( float4 r)
	{
		//float x_ = a.GetY() * r.GetZ() - a.GetZ() * r.GetY();
		//float y_ = a.GetZ()* r.GetX() - a.GetX() * r.GetZ();
		//float z_ = a.GetX()* r.GetY() - a.GetY()* r.GetX();

		float x_ = GetY() * r.GetZ() - GetZ() * r.GetY();
		float y_ = GetZ()* r.GetX() - GetX() * r.GetZ();
		float z_ = GetX()* r.GetY() - GetY()* r.GetX();
		return  float4(x_, y_, z_, 0);
	}

	float4 Normalized()
	{
		float length = 1 / Length();

		return float4(m_x * length, m_y * length, m_z * length, m_w* length);
	}

	float4 Rotate(float4 axis, float angle)
	{
		float sinAngle = (float)sin(-angle);
		float cosAngle = (float)cos(-angle);

		float4 cur(m_x, m_y, m_z, m_w);

		return cur.cross(axis*(sinAngle)) + (           //Rotation on local X
			(cur*(cosAngle)) + (						//Rotation on local Z
				axis*(cur.dot( axis*(1 - cosAngle))))); //Rotation on local Y
	}


	float4 Lerp(float4 dest, float lerpFactor)
	{
		float4 cur(m_x, m_y, m_z, m_w);
		return dest - cur*(lerpFactor)+cur;
	}

	float4 operator+(float4 r)
	{
		return float4(m_x + r.GetX(), m_y + r.GetY(), m_z + r.GetZ(), m_w + r.GetW());
	}

	float4 operator+(float r)
	{
		return float4(m_x + r, m_y + r, m_z + r, m_w + r);
	}

	float4 operator-(float4 r)
	{
		return float4(m_x - r.GetX(), m_y - r.GetY(), m_z - r.GetZ(), m_w - r.GetW());
	}

	float4 operator-(float r)
	{
		return float4(m_x - r, m_y - r, m_z - r, m_w - r);
	}

	float4 operator*(float4 r)
	{
		return  float4(m_x * r.GetX(), m_y * r.GetY(), m_z * r.GetZ(), m_w * r.GetW());
	}

	float4 operator*(float r)
	{
		return  float4(m_x * r, m_y * r, m_z * r, m_w * r);
	}

	float4 operator/(float4 r)
	{
		return  float4(m_x / r.GetX(), m_y / r.GetY(), m_z / r.GetZ(), m_w / r.GetW());
	}

	float4 operator/(float r)
	{
		return  float4(m_x / r, m_y / r, m_z / r, m_w / r);
	}

	float4 Abs()
	{
		return  float4(abs(m_x), abs(m_y), abs(m_z), abs(m_w));
	}

	//public String toString()
	//{
	//	return "(" + x + ", " + y + ", " + z + ", " + w + ")";
	//}

	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetZ() { return m_z; }
	float GetW() { return m_w; }
	//void SetX(float x) { m_x = x; }
	//void SetY(float y) { m_y = y; }
	//void SetZ(float z) { m_z = z; }
	//void SetW(float w) { m_w = w; }

	bool operator==(float4 r)
	{
		return m_x == r.GetX() && m_y == r.GetY() && m_z == r.GetZ() && m_w == r.GetW();
	}
};