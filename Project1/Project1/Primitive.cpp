#include "Primitive.h"


Primitive::Primitive()
{
	//	m_material = &Material::DBLUE_D;
}


Primitive::~Primitive()
{
//	delete m_color;
}

Color Primitive::getColor() 
{
	return m_material->getColor();
	//	*m_color; 
}

Material Primitive::getMaterial() { return *m_material; }


HitInfo Primitive::Intersect(Ray& ray, float distance)
{
	return HitInfo (float3 (0,0,0), float3(0,0,0), Color(0,0,0), -1);
}
 
void Primitive::setColor(Color &color)
{
 //	m_color =&color;
}

void Primitive::setMaterial(Material& material)
{
	m_material = &material;
}
