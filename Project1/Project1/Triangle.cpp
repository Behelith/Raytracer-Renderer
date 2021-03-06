#include "Triangle.h"
//#include <Brofiler.h>


Triangle::Triangle() //: m_verts[0](float3(0,0,0)), m_b(float3(0, 0, 0)), m_c(float3(0, 0, 0))
{
//	m_vertices = new
	//m_verts[0] = float3(0, 0, 0); //v0
	//m_verts[1] = float3(0, 0, 0); //v1
	//m_verts[2] = float3(0, 0, 0); //v2
}

/*
Triangle::Triangle(float3* a, float3 *b, float3* c, Material &material)// : m_a(a), m_b(b), m_c(c)
{
	m_verts.push_back(a);
	m_verts.push_back(b);
	m_verts.push_back(c);

//	m_normal = float3::cross((c - a), (b - a));
	m_normal = float3::cross( (*b - *a), (*c - *a));
	m_normal.unitise();

	setMaterial(material);
}
*/

Triangle::Triangle(vector<int> indecies, Material& material)
{
	m_indecies = indecies;
	m_normal.normalize();

	setMaterial(material);

}

Triangle::~Triangle()
{
	//delete	m_vertices;
//	delete m_uvs;
	//m_verts.clear();
}

void Triangle::setColor(Color &color)
{
	//	m_color =&color;
}

Color Triangle::getColor(float3 point)
{
	//	if (!getMaterial().getIsTextured())
	//return getMaterial().getColor();
	return Color::GREEN;
	//else
	//{
	//	// pole trojkata abc =  || (b - a) X (c-a) || /2;

	//	//float3 e1 = *m_verts[1] - *m_verts[0];
	//	//float3 e2 = *m_verts[2] - *m_verts[0];

	//	float abc= float3::cross(*m_verts[1] - *m_verts[0], *m_verts[2] - *m_verts[0]).length()*0.5f;

	//	// u = cap/ abc
	//	float cap = float3::cross(*m_verts[0] - *m_verts[2], point - *m_verts[2]).length()*0.5f;
	//	// v = abp / abc
	//	float abp = float3::cross(*m_verts[1] - *m_verts[0], point - *m_verts[0]).length()*0.5f;

	//	float u = cap / abc;
	//	float v = abp / abc;


	//	int x = (u* m_material->getTexture().getWidth());
	//	int y = (v* m_material->getTexture().getHeight());

	//	return Color(m_material->getTexture().getComponents()[x + y*m_material->getTexture().getWidth()]);
	//}
	//return *m_color;
}

HitInfo Triangle::Intersect(Ray& ray, float distance, float3 a, float3 b, float3 c, float3 *uvw)
{
	//BROFILER_CATEGORY ("intersect", Profiler::Color::Green)


	float3 e1 = b - a;
	float3 e2 = c - a;

	// z rozwiazania macierzy
	//P = D x e2
	//Q = T x e1
	// T = rayOrigin -A (v0)
	//float3 n = float3::cross(e1, e2);
	float3 p = float3::cross(ray.getDirection(), e2);
	float det = float3::dot(e1, p); // wyznacznik macierzy


									//culling: jesli to prawdzwe, to trojkat jest tylem; jesli jest blisko zera to nie trafia w trojkat;
									//cout << det << endl;
	if (-eps5 < det < eps5)
		//if (det > -eps5 && det < eps5)
		return HitInfo(float3(0, 0, 0), float3(0, 0, 0), Color::GREEN, -1);
	//	return -1;

	//if (fabs(det) < eps5) 
	//	return -1;


	float iDet = 1.f / det;

	float3 t = ray.getOrigin() - a;
	m_u = float3::dot(t, p) * iDet;
	if (m_u < 0 || m_u > 1)// return -1.f;
		return HitInfo(float3(0, 0, 0), float3(0, 0, 0), Color::RED, -1);
	//cout << m_u << endl;

	float3 q = float3::cross(t, e1);

	m_v = float3::dot(ray.getDirection(), q) * iDet;
	if (m_v < 0 || m_u + m_v > 1)// return -1.f;


		return HitInfo(float3(), float3(), Color::RED, -1);

	//cout << m_v << endl;

	m_w = float3::dot(e2, q)* iDet;



	if (m_w > eps5)
	{
		float3 point = ray.getOrigin() + ray.getDirection()*m_w;

		//normalna sie liczy tak:
		float3 n = float3::cross(e1, e2);
		n.normalize();

		//return HitInfo(getNormal(), p, Color::WHITE, m_w);
		return HitInfo(n, point, getColor(point), m_w);
		//	return m_w;
	}

	uvw = new float3(m_u, m_v, m_w);
	return HitInfo(float3(0, 0, 0), float3(0, 0, 0), Color::RED, -1);
}
