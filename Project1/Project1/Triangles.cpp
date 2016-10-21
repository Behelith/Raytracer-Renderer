#include "Triangles.h"

Triangles::Triangles(int number, float spread, float speed)
{
	m_speed = speed;
	m_spread = spread;
	m_number = number;

	m_starX = new float[number];
	m_starY = new float[number];
	m_starZ = new float[number];

	m_triangles = new Triangle[number];


	FOV = 40.0f;


	for (int i = 0; i < m_number; i++)
	{
		InitStar(i);
	}

}

void Triangles::updateAndRender(RenderContext *bitmap, float delta, float fov)
{
	
	bitmap->Clear(0x120c0000);
	unsigned int color;
	int hWidth = bitmap->getWidth() / 2,
		hHeight = bitmap->getHeight() / 2;
	float pi180 = 3.14159265359f / 180.0f;
	// to radians: degrees * pi / 180
	//cout << tanHFOV << endl;

	float tanHFOV = (float)tan((fov * pi180) / 2.0f);//tanges (fov /2)

	for (int i = 0; i < m_number; i++)
	{

		int val = (int)(255 * m_starZ[i]);
		color = (val << 24 | val << 16);
		//cout << hex << color << endl;

		m_starZ[i] -= delta * m_speed;
		if (m_starZ[i] <= 0) InitStar(i);

		/*
		int x1 = (int)((m_triangles[i].m_a.x / (tanHFOV*m_triangles[i].m_a.z)) * hWidth + hWidth);
		int y1 = (int)((m_triangles[i].m_a.y / (tanHFOV*m_triangles[i].m_a.z))* hHeight + hHeight);

		int x2 = (int)((m_triangles[i].m_b.x / (tanHFOV*m_triangles[i].m_b.z)) * hWidth + hWidth);
		int y2 = (int)((m_triangles[i].m_b.y / (tanHFOV*m_triangles[i].m_b.z))* hHeight + hHeight);

		int x3 = (int)((m_triangles[i].m_c.x / (tanHFOV*m_triangles[i].m_c.z)) * hWidth + hWidth);
		int y3 = (int)((m_triangles[i].m_c.y / (tanHFOV*m_triangles[i].m_c.z))* hHeight + hHeight);
		

		if (x1 < 0 || x1 >= bitmap->getWidth() ||
			y1 < 0 || y1 >= bitmap->getHeight())
		{
			m_triangles[i].m_a

		}*/
		else
		{

			//triangle[i] = float2(x, y);
			/*			float2 a(m_starX[0], m_starY[0]);
			float2 b(m_starX[1], m_starY[1]);
			float2 c(m_starX[2], m_starY[2]);*/
			float2 a = float2(100, 100), b = float2(100, 200), c = float2(80, 300);
			//tris[i] = float2(x, y);
			//	cout << m_starX[0] << endl;

			
		//	bitmap->FillTriangle(triangle[i], triangle[i+1], triangle[i+2]);
			//bitmap->FillTriangle(triangle[0], b, c);



			//bitmap->DrawPixel(x, y, 0x00fd09ff);
			//bitmap->DrawPixel(x, y, color);
		}
	}

}

float3 Triangles::InitStar(int index)
{
	return float3(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
		2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread
		);

//	m_triangles[i].
	/*m_triangles[index] = Triangle
		(
			float3(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
				2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
				(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread), 

			float3(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
					2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
					(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread),

			float3(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
						2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread,
						(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread)
			);*/

/*	m_starX[index] = 2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread;
	m_starY[index] = 2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread;
	m_starZ[index] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread;*/

}



Triangles::~Triangles()
{
}
