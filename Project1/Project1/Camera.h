#pragma once
#include "structures.h"
#include "RenderContext.h"
#include "Sphere.h"
#include "Ray.h"

class Camera
{
private:
	float3 m_location;
	float3 m_direction;
	float3 m_target;
	float3 m_up;
	float  m_fov;
	float  m_distance;
	float3 m_u, m_v, m_w;
	// czy kamera definiuje bitmape, czy powinna wiedziec do jakiej bitmapy renderowac? oto jest pytanie
	// int m_w, m_h;


public:
	Camera();
	Camera(float3 location, float3 direction, float3 up, float fov);
	
	~Camera();

	void LookAt(float3 target);
	void RenderImage (RenderContext &bitmap, Sphere *objects);
};

