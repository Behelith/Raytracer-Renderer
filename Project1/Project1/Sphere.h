#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(float3 center, float radius, Material &material);
	~Sphere() {};
	
	Color getColor(float3 point)
	{
		if (!m_material->getIsTextured())
		return m_material->getColor();
		{
			float3 lp = point - center;
			float yDIVr = lp.y / radius;
			float pi2 = 3.14159265359f * 2;
			float pi = 3.14159265359f;

			float v =
				(abs(yDIVr - 1.0f) < eps5) ? 0.0f : // v = 0 (górny biegun)
				(abs(yDIVr + 1.0f) < eps5) ? 1.0f : // v = 1 (dolny biegun)
				acos(yDIVr) / pi;
				
				float rMULsin = radius * sin(3.14159265359f*v);
			float u = // 1,2 -> biegun // 3,4 -> |x/rMULsin|=1 -> acos nieokreœlony
				(abs(v) < eps5) ? 0.0f :               // 1) (u,v) = (0.0, 0)
				(abs(v - 1.0f) < eps5) ? 0.0f :        // 2) (u,v) = (0.0, 1)
				(abs(lp.x - rMULsin) < eps5) ? 0.0f :  // 3) (u,v) = (0.0, v) 
				(abs(lp.x + rMULsin) < eps5) ? 0.5f :  // 4) (u,v) = (0.5, v)
				acos(lp.x / rMULsin) / pi2;               // bez osobliwoœci
			

			float3(
				center.x + radius * sin(pi * v) * cos(pi2 * u),
				center.y +radius * cos(pi * v),
				center.z +radius * sin(pi * v) * sin(pi2 * u)
			);

			int x = (u * m_material->getTexture().getWidth());
			int y = (v * m_material->getTexture().getHeight());

			return Color(m_material->getTexture().getComponents()[x + y*m_material->getTexture().getWidth()]);
		}
	}
	float3 getNormal(float3 & position);
	float3 getCenter() { return center; }
	float getRadius() { return radius; }
	void setCenter(float3 newCenter){		center = newCenter;	}
    HitInfo Intersect(Ray &ray, float distance);

private:
	float3 center;
	float radius;
};
	