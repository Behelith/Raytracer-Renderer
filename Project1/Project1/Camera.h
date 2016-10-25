#pragma once
#include "structures.h"
#include "RenderContext.h"
#include "Sphere.h"

class Camera
{
protected:
	float3 m_location;
	float3 m_direction;
	float3 m_target;
	float3 m_up;
	float3 m_u, m_v, m_w;


public:
	Camera();
	~Camera();

	void RenderImage(RenderContext &bitmap, Sphere *objects);
	float3 getLocation() { return m_location; }
	void setLocation(float3 location) { m_location = location; }
	float3 getDirection() { return m_direction; }
	void setDirection(float3 direction) { m_direction = direction; }

};

