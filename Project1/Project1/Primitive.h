#pragma once
#include "structures.h"
#include "Color.h"
#include "Ray.h"
#include "Material.h"
#include "HitInfo.h"

class Primitive
{
public:
	Primitive();
	~Primitive();
	//float3 getCenter() { return center; }
	virtual Color getColor(float3 point);
	virtual HitInfo Intersect(Ray &ray, float distance);
	virtual void setColor(Color &color);
	virtual void setMaterial(Material &material);
	virtual Material getMaterial();
	
protected:
	float3 center;
	//unsigned int m_color;
//	Color *m_color;
	Material *m_material;
};

