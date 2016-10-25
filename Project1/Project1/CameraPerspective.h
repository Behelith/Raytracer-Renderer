#pragma once
#include "structures.h"
#include "RenderContext.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"

class CameraPerspective : public Camera
{
protected:
	//float3 m_location;
	//float3 m_direction;
	//float3 m_target;
	//float3 m_up;
	//float3 m_u, m_v, m_w;

	float  m_fov;
	float  m_distance;
	// czy kamera definiuje bitmape, czy powinna wiedziec do jakiej bitmapy renderowac? oto jest pytanie
	// int m_w, m_h;


public:
	CameraPerspective();
	CameraPerspective(float3 location, float3 direction, float3 up, float fov);
	
	~CameraPerspective();

	void LookAt(float3 target);
	void RenderImage (RenderContext &bitmap, Sphere *objects);
};

