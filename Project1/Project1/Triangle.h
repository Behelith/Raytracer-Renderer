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
	vector <float3*> m_verts;
	vector <float2> m_uv;
	Triangle();
	//Triangle(float3 &a, float3 &b, float3 &c, Color &color);
	Triangle(float3 *a, float3* b, float3* c, Material &material);
	~Triangle();

	float3 getNormal() { return m_normal; }
	void setUV(float2 p1, float2 p2, float2 p3)
	{
		// punkty u,v
		m_uv.push_back(p1);
		m_uv.push_back(p2);
		m_uv.push_back(p3);
	}


	void setColor(Color &color);
	Color getColor(float3 point)
	{
		if (!getMaterial().getIsTextured())
			return getMaterial().getColor();
		else
		{
			// pole trojkata abc =  || (b - a) X (c-a) || /2;

			//float3 e1 = *m_verts[1] - *m_verts[0];
			//float3 e2 = *m_verts[2] - *m_verts[0];

			float abc= float3::cross(*m_verts[1] - *m_verts[0], *m_verts[2] - *m_verts[0]).length()*0.5f;

			// u = cap/ abc
			float cap = float3::cross(*m_verts[0] - *m_verts[2], point - *m_verts[2]).length()*0.5f;
			// v = abp / abc
			float abp = float3::cross(*m_verts[1] - *m_verts[0], point - *m_verts[0]).length()*0.5f;

			float u = cap / abc;
			float v = abp / abc;



			int x = (u* m_material->getTexture().getWidth());
			int y = (v* m_material->getTexture().getHeight());

			return Color(m_material->getTexture().getComponents()[x + y*m_material->getTexture().getWidth()]);
		}
		//return *m_color;
	}

	HitInfo Intersect(Ray &ray, float distance);
};

