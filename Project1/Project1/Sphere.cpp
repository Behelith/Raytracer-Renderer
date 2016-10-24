#include "Sphere.h"




Sphere::Sphere()
{
	delete m_color;
}

Sphere::Sphere(float3 center, float radius) : center(center), radius(radius)
{
	m_color = new Color(1.0f, 0.0f, 0.0f);

}

float3 Sphere::getNormal(float3& position) {
	float3 ret = position - center;
	ret.normalize();
	return ret;
	//m_color = 0xccdd0000;
	//setColor(Color(1.0f, 0.0f, 0.0f));
	//  return ((position - center) * inverseRadius);
}
