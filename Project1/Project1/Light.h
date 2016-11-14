#pragma once
#include "structures.h"

class Light
{
protected:
	float3 m_position;
	Color m_color;
	float m_constAtt;
	float m_linearAtt;
	float m_quadAtt;


	/* 
	 * dodac ----------- ENUM lightTYPE;
	* -1- default
	* 1 - point

	*/
	int m_lightType;

public:
	Light();
	Light(float3 position, Color &color);
	~Light();

	Color getColor() { return m_color; }
	float3 getPosition() { return m_position; }
	int getLightType() { return m_lightType; }
	float getConstA() { return m_constAtt; }
	float getLinearA() { return m_linearAtt; }
	float getQuadA() { return m_quadAtt; }
	//	float getG ()
};

