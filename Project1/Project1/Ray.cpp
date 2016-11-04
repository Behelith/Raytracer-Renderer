#include "Ray.h"


Ray::Ray() : m_origin(float3(0, 0, 0)), m_direction(float3(0, 0, 0)), m_negdirection(-m_direction) {}
Ray::Ray(float3 origin, float3 direction) : m_origin(origin), m_direction(direction), m_negdirection(-direction) {}
//*

/*
float Ray::intersect(Plane &plane, float distance)
{
	float a = float3::dot(plane.getNormal(), getDirection());
	float tmp = -1;
	if (a > 0) tmp = (plane.getDistance() - float3::dot(plane.getNormal(), getOrigin())) / a;

	if (tmp < 0)
	{
		if (a == 0) cout << "promien i plaszczyzna sa prostopadle" << endl;
		cout << "brak punktu przeciecia" << endl;
		return tmp;
	}
	else
	{
		float3 p(getOrigin() + getDirection() * tmp);
		cout << "punkt przeciecia w zadanym kierunku: " << p << endl;
	}
	return tmp;
}
*/