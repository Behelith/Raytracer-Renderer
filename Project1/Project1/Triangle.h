#pragma once
#include "structures.h"
#include "Primitive.h"

class Triangle : public Primitive
{
private:
	float3 m_normal;
	float m_u, m_v, m_w;
	//Color *m_color;

public:
	//float3 m_verts[3];


	vector <int> m_indecies;
//	vector <float3*> m_verts;
	//vector <float2> m_uv;


	Triangle();
	//Triangle(float3 &a, float3 &b, float3 &c, Color &color);
	//Triangle(float3 *a, float3* b, float3* c, Material &material);
	Triangle(vector<int> indecies, Material &material);
	~Triangle();

	float3 getNormal() { return m_normal; }
	void setColor(Color &color);
	Color getColor(float3 point);

	HitInfo Intersect(Ray& ray, float distance, float3 a, float3 b, float3 c, float3 *uvw);
};

