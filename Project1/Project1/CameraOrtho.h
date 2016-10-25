#pragma once
#include "CameraPerspective.h"

class CameraOrtho : public CameraPerspective
{
public:
	CameraOrtho();
	CameraOrtho(float3 location, float3 direction, float3 up);
	void RenderImage(RenderContext &bitmap, Sphere *objects);


	~CameraOrtho();


};

