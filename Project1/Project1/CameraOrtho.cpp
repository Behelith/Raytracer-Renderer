#include "CameraOrtho.h"



CameraOrtho::CameraOrtho()
{
}

CameraOrtho::CameraOrtho(float3 location, float3 direction, float3 up)
{
	m_target = direction; m_up = up;
	m_location = location;

	m_direction = m_location - m_target;

	m_w = m_direction;// prosto
	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
									//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 5;
	m_u = -m_u;
}

void CameraOrtho::RenderImage(RenderContext &bitmap, Sphere *objects)
{



	float *zBuffer = new float[bitmap.getWidth() * bitmap.getHeight()];
	fill(zBuffer, zBuffer + (bitmap.getWidth() * bitmap.getHeight()), INFINITY);
	float zMin = INFINITY, zMax = 0;
	float aspectRatio = float(bitmap.getWidth()) / float(bitmap.getHeight());


	//float pi180 = 3.14159265359f / 180.0f;
	float tanHFOV = 1;

	float pxc, pyc;

	for (int x = 0; x < bitmap.getWidth(); x++)

	{

		for (int y = 0; y < bitmap.getHeight(); y++)
		{
			if (aspectRatio <= 1)
			{
				pxc = (2 * (x + 0.5) / (float)bitmap.getWidth() - 1) * tanHFOV;
				pyc = (2 * (y + 0.5) / (float)bitmap.getHeight() - 1)  * tanHFOV / aspectRatio;
			}
			else
			{
				pxc = (2 * (x + 0.5) / (float)bitmap.getWidth() - 1) * tanHFOV * aspectRatio;
				pyc = (1 - 2 * (y + 0.5) / (float)bitmap.getHeight()) * tanHFOV;
			}

			float3 pxRay = m_u * pxc + m_v * pyc + m_w * -m_distance;
			//float3 pxRay (pxc, pyc, 0);
			//pxRay.unitise();
			//float3 eye = m_u * pxc + m_v * pyc + m_w * 0;

			//pxRay.unitise();
			Ray r(pxRay, m_w);//float3(0, 0, 1));
			for (int i = 0; i < 3; i++) {

				float isect = r.intersect(objects[i], 50);


				if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
				{
					zBuffer[x + y *bitmap.getWidth()] = isect;
					if (isect > zMax) zMax = isect;
					if (isect < zMin) zMin = isect;

					Color tmpCol = objects[i].getColor();// *(1 - pr);
					bitmap.DrawPixel(x, y, tmpCol.toHex());
				}
			}
		}
	}

}


CameraOrtho::~CameraOrtho()
{
}
