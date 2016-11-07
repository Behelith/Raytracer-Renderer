#include "Triangle.h"
#include <Brofiler.h>


Triangle::Triangle() //: m_verts[0](float3(0,0,0)), m_b(float3(0, 0, 0)), m_c(float3(0, 0, 0))
{
	//m_verts[0] = float3(0, 0, 0); //v0
	//m_verts[1] = float3(0, 0, 0); //v1
	//m_verts[2] = float3(0, 0, 0); //v2
}

Triangle::Triangle(float3* a, float3 *b, float3* c, Color &color)// : m_a(a), m_b(b), m_c(c)
{
	m_verts.push_back(a);
	m_verts.push_back(b);
	m_verts.push_back(c);

	/*	m_verts[0] = a;
	m_verts[1] = b;
	m_verts[2] = c;*/
	/*if (a.y < b.y)
	{
		float3 tmp = b;
		b = a;
		a = tmp;

	}
	if (b.y < c.y)
	{
		float3 tmp = c;
		c = b;
		b = tmp;
	}
	if (a.y < b.y)
	{
		float3 tmp = b;
		b = a;
		a = tmp;
	}*/



//	m_normal = float3::cross((c - a), (b - a));
	m_normal = float3::cross( (*b - *a), (*c - *a));

	setColor(color);
}

Triangle::~Triangle()
{
	m_verts.clear();
}

float Triangle::Intersect(Ray& ray, float distance)
{
	BROFILER_CATEGORY ("intersect", Profiler::Color::Green)

	//edge 1
	float3 e1 = *m_verts[1] - *m_verts[0];
	float3 e2 = *m_verts[2] - *m_verts[0];

	// z rozwiazania macierzy
	//P = D x e2
	//Q = T x e1
	// T = rayOrigin -A (v0)
	//float3 n = float3::cross(e1, e2);
	float3 p = float3::cross(ray.getDirection(), e2);
	float det = float3::dot(e1, p); // wyznacznik macierzy


	//culling: jesli to prawdzwe, to trojkat jest tylem; jesli jest blisko zera to nie trafia w trojkat;
	//cout << det << endl;
	if (det < 0.000005)
		return -1;

	if (fabs(det) < 0.000005) 
		return -1;

	
//	float iDet = 1 / det;

	float3 t = ray.getOrigin() - *m_verts[0];
	m_u = float3::dot(t, p) / det;
	if (m_u < 0 || m_u > 1) return -1;
	//cout << m_u << endl;

	float3 q = float3::cross(t, e1);
	m_v = float3::dot(ray.getDirection(), q) / det;
	if (m_v < 0 || m_u + m_v > 1) return -1;
	//cout << m_v << endl;

	m_w = float3::dot(e2, q) / det;

	
	//cout << "m_w: " << m_w << endl;


	return (p - ray.getOrigin()).length();
}
