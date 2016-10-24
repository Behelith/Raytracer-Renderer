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
	m_v = float3::cross(m_w, m_u); //

	m_distance = 20;



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
	m_v = float3::cross(m_w, m_u); //
}

void Camera::RenderImage(RenderContext& bitmap, Sphere * objects)
{


	float *zBuffer = new float[bitmap.getWidth() * bitmap.getHeight()];
	fill(zBuffer, zBuffer + (bitmap.getWidth() * bitmap.getHeight()), INFINITY);

	float aspectRatio = float(bitmap.getWidth()) / float(bitmap.getHeight());
	

	float pi180 = 3.14159265359f / 180.0f;	
	float tanHFOV = float(tan((m_fov * pi180) / 2.0f));//tangens (fov /2)

	float halfHeight = aspectRatio* tanHFOV;
	float camerawidth = tanHFOV * 2;
	float cameraheight = halfHeight * 2 ;


	float pw = camerawidth / bitmap.getWidth(),
	ph = cameraheight / bitmap.getHeight();


	float near = .1f, far = 9.0f;
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
				pyc = (2 * (y + 0.5) / (float)bitmap.getHeight() - 1) * tanHFOV;
			}

			pw = 2.0f / bitmap.getWidth();
			ph = 2.0f / bitmap.getHeight();


			//	pxc = -1.0f + (x + 0.5f) * pw;
			//	pyc = 1.0f - (y + 0.5f) * ph;



				//float3 pxRay(pxc, pyc, 0);
			float3 pxRay = m_u * pxc + m_v * pyc + m_w * -m_distance;

			pxRay.unitise();
			//return onb * new Vector3(v.X, v.Y, -distance);

			Ray r(m_location, pxRay);


			//Ray r(pxRay, float3(0, 0, 1));
			// onb.u * v.X + onb.v * v.Y + onb.w * v.Z);
			//float3 sd = m_u * x + m_v * y + m_w * -m_distance;

			for (int i = 0; i < 3; i++) {

				float isect = r.intersect(objects[i], 50);


				if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
				{
					zBuffer[x + y *bitmap.getWidth()] = isect;
					//Color tmpCol(0.0f, 0.3f, 1.0f);
					//Color tmpCol(1.0f * (1 - pr* isect), 1.0f * (1-pr* isect), 1.0f * (1-pr* isect));
					pr = 1 - far / isect;
					Color tmpCol(1.0f - 1.0f * pr, 1.0f - 1.0f * pr, 1.0f - 1.0f * pr);

					//if (i != 0)	tmpCol = Color(0.3f, 1.0f, 0.0f);

					bitmap.DrawPixel(x, y, tmpCol.toHex());
				}
			}
		}
	}

}
