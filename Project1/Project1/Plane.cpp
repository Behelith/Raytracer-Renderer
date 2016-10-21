#include "Plane.h"


Plane::Plane() : m_normal(0, 0, 1), m_distance(0) {};
Plane::Plane(float3 normal, float distance) : m_normal(normal), m_distance(distance) {};
float3& Plane::getNormal() { return m_normal; }
float Plane::getDistance() { return m_distance; }