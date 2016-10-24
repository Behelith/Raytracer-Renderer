#include "Camera.h"

/*TODO odwrocic kamere, bo jest odwrotnie gora z dolem i lewo z prawa strona
abstrakcyjna klasa dla kamery, co by mozna bylo renderowac i ortho
*/

Camera::Camera()
{
}

Camera::Camera(float3 location, float3 direction, float3 up, float fov) : m_location(location), m_target(direction), m_up(up), m_fov(fov)
{
	m_direction = m_location - m_target;
	
	m_w = m_direction;// prosto
	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
	//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;
	m_u = -m_u;
}

Camera::~Camera()
{
}

void Camera::LookAt(float3 target)
{
	m_target = target;
	m_direction = m_location - m_target;

	m_w = m_direction;// prosto
	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
									//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;
	m_u = -m_u;

}

void Camera::RenderImage(RenderContext& bitmap, Sphere * objects)
{


	float *zBuffer = new float[bitmap.getWidth() * bitmap.getHeight()];
	fill(zBuffer, zBuffer + (bitmap.getWidth() * bitmap.getHeight()), INFINITY);
	float zMin = INFINITY, zMax = 0;
	float aspectRatio = float(bitmap.getWidth()) / float(bitmap.getHeight());
	

	float pi180 = 3.14159265359f / 180.0f;	
	float tanHFOV = float(tan((m_fov * pi180) / 2.0f));//tangens (fov /2)

	//float ph, pw;
	//pw = 2.0f / bitmap.getWidth();
	//ph = 2.0f / bitmap.getHeight();





	//float halfHeight = aspectRatio* tanHFOV;
	//float camerawidth = tanHFOV * 2;
	//float cameraheight = halfHeight * 2 ;


	//float pw = camerawidth / bitmap.getWidth(),
	//ph = cameraheight / bitmap.getHeight();


	float near = 0.1f, far = 9.0f;
	float pr;

	
	
	float pxc, pyc;

	for (int x = 0; x < bitmap.getWidth(); x++)

	{

		for (int y = 0; y < bitmap.getHeight(); y++)
		{
			if (aspectRatio <= 1)
			{
				pxc = (2 * (x + 0.5) / (float)bitmap.getWidth() - 1) * tanHFOV;
				pyc = (2 * (y + 0.5) / (float)bitmap.getHeight() - 1) / aspectRatio * tanHFOV;
			}
			else
			{
				pxc = (2 * (x + 0.5) / (float)bitmap.getWidth() - 1) * tanHFOV * aspectRatio;
				pyc = (1 -2 * (y + 0.5) / (float)bitmap.getHeight() ) * tanHFOV;
			}

			float3 pxRay = m_u * pxc + m_v * pyc + m_w * -m_distance;

			pxRay.unitise();
			Ray r(m_location, pxRay);
			for (int i = 0; i < 3; i++) {

				float isect = r.intersect(objects[i], 50);


				if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
				{
					zBuffer[x + y *bitmap.getWidth()] = isect;
					if (isect > zMax) zMax = isect;
					if (isect < zMin) zMin = isect;

					pr = 0;
					Color tmpCol = objects[i].getColor();// *(1 - pr);
					bitmap.DrawPixel(x, y, tmpCol.toHex());
				}
			}
		}
	}

	/*
		float d = zMax - zMin;
		for (int i = 0; i < bitmap.getHeight() * bitmap.getWidth(); i++)
		{
			if (zBuffer[i] < INFINITY)
			{
				float pr = (zBuffer[i]-zMin )/ d;
				//Color col = Color(1.f, 1.f, 1.f) * (1 - pr);
				Color col = Color(bitmap.getComponents()[i]) * (1 - pr);

			 bitmap.getComponents()[i] = col.toHex();

			}
			else bitmap.getComponents()[i] = Color(0.0f, 0.f, 0.f).toHex();
		}
	*/

}
