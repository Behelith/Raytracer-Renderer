#pragma once
#include "float3.h"
#include "Color.h"

class HitInfo
{
private:
	float3 m_normal;
	float3 m_point;
	Color m_color;
	int m_tIndex;
	float m_distance;
	float m_u;
	float m_v;
public:
	HitInfo();
	HitInfo(float3 normal, float3 point, Color color, float distance);
	
	float getDistance() { return m_distance; }
	float3 getPoint() { return m_point; }
	float3 getNormal() { return m_normal; }
	Color getColor() { return m_color; } // ??

	void setTIndex(int tIndex) { m_tIndex = tIndex; }
	int getTIndex() { return m_tIndex; }

	void setU(float u) { m_u = u; }
	void setV(float v) { m_v = v; }
	float getU() { return m_u; }
	float getV() { return m_v; }

	void setColor(Color color)
	{
		m_color = color;
	}

	~HitInfo();
};

