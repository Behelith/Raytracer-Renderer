#include "Triangle.h"



Triangle::Triangle() //: m_verts[0](float3(0,0,0)), m_b(float3(0, 0, 0)), m_c(float3(0, 0, 0))
{
	m_verts[0] = float3(0, 0, 0);
	m_verts[1] = float3(0, 0, 0);
	m_verts[2] = float3(0, 0, 0);
}

Triangle::Triangle(float3 a, float3 b, float3 c)// : m_a(a), m_b(b), m_c(c)
{
	m_verts[0] = a;
	m_verts[1] = b;
	m_verts[2] = c;
}

Triangle::~Triangle()
{
}
