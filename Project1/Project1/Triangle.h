#pragma once
#include "structures.h"
#include "Primitive.h"

class Triangle : public Primitive
{
private: 
	float3 m_normal;
	float m_u, m_v, m_w;
	Color *m_color;


public:
	//float3 m_verts[3];
	vector <float3*> m_verts;
	Triangle();
	//Triangle(float3 &a, float3 &b, float3 &c, Color &color);
	Triangle(float3 *a, float3* b, float3* c, Color &color);
	~Triangle(); 

	float3 getNormal() { return m_normal; }

	void setColor(Color &color);
	Color getColor() { return *m_color; }

	HitInfo Intersect(Ray &ray, float distance);
};

