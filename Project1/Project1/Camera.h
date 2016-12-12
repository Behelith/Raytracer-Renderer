#pragma once
#include "structures.h"
#include "RenderContext.h"
#include "Primitive.h"
//#include "Ray.h"
#include "Sphere.h"
#include "Light.h"

class Camera
{
protected:
	float3 m_location;
	float3 m_direction;
	float3 m_target;
	float3 m_up;
	float3 m_u, m_v, m_w;

	float  m_fov;
	float  m_distance;
	bool isOrthogonal;
	// czy kamera definiuje bitmape, czy powinna wiedziec do jakiej bitmapy renderowac? oto jest pytanie
	// int m_w, m_h;


public:
	Camera();

	//kamera perspektywiczna
	Camera(float3 location, float3 direction, float3 up, float fov);
	// kamera ortogonalna
	Camera(float3 location, float3 direction, float3 up);

	~Camera();

	void LookAt(float3 target);
	Color Sampling(float2 sCenter, float2 dimensions, vector<Primitive*> &objects, vector<Light*> &lights, float &zDepth, int level = 0);
	Color GetColor(Ray ray, int lvl, vector<Primitive*> &objects, vector<Light*> &lights, float &zDepth);
	void RenderImage(RenderContext &bitmap, vector<Primitive*> &objectss, vector<Light*> &lights);
};

