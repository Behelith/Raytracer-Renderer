#include "HitInfo.h"


HitInfo::HitInfo()
{
	m_normal = float3(0,0,0);
	m_point = float3(0,0,0);
	m_color = Color::RED;
	m_distance = -1;
	m_tIndex = -1;
}

HitInfo::HitInfo(float3 normal, float3 point, Color color, float distance)
{
	m_normal = normal;
	m_point = point;
	m_color = color;
	m_distance = distance;
	m_tIndex = -1;
}

HitInfo::~HitInfo()
{
//	delete m_color;
}
