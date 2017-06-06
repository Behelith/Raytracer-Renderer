#include "Stars3D.h"

Stars3D::Stars3D(int number, float spread, float speed, int mode)
{
	renderMode = mode;
	m_speed = speed;
	m_spread = spread;
	m_number = number;

	m_starX = new float[number];
	m_starY = new float[number];
	m_starZ = new float[number];

	m_stars = new float4[number];

	FOV = 40.0f;


	for (int i = 0; i < m_number; i++)
	{
		InitStar(i);
	}
}

void Stars3D::updateAndRender(RenderContext &bitmap, float delta, float fov)
{
	//bitmap.Clear(0x120c0000);			// clearScreen
	bitmap.Clear(0x0f000f00);			// clearScreen

	int hWidth = bitmap.getWidth() / 2,
		hHeight = bitmap.getHeight() / 2;
	float tanHFOV = float(tan((fov * PI180) / 2.0f));//tangens (fov /2)


	
	if (renderMode == 0)
		for (int i = 0; i < m_number; i++)
		{
			m_stars[i].m_z -= delta* m_speed;

			if (m_stars[i].m_z <= 0) InitStar(i);

			int x = int((m_stars[i].m_x / (tanHFOV *m_stars[i].m_z)) * hWidth + hWidth);
			int y = int((m_stars[i].m_y / (tanHFOV *m_stars[i].m_z)) * hHeight + hHeight);

			if (x < 0 || x >= bitmap.getWidth() ||
				y < 0 || y >= bitmap.getHeight())
				InitStar(i);
			else
			{
				unsigned int color = 0xff00ff00;
				bitmap.DrawPixel(x, y, color);
			}
		}

	else if (renderMode == 1)
	{

		unsigned int color;

		int triangleBuilderCounter = 0;

		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;

		float tanHFOV = float(tan((fov * PI180) / 2.0f));//tangens (fov /2)

		for (int i = 0; i < m_number; i++)
		{

			//int val = int(255 * m_starZ[i]);
			int val = int(255 * m_stars[i].m_z);
			color = (val << 24 | val << 16);
			//cout << hex << color << endl;

	/*		m_starZ[i] -= delta * m_speed;
			if (m_starZ[i] <= 0) InitStar(i);*/
			m_stars[i].m_z -= delta * m_speed;
			if (m_stars[i].m_z <= 0) InitStar(i);
			
				// dzielenie przez wspolrzedna Z (tangens pola widzenia * Z) sprawia wrazenie 3d
			int x = int((m_stars[i].m_x / (tanHFOV * m_stars[i].m_z)) * hWidth + hWidth);
			int y = int((m_stars[i].m_y / (tanHFOV * m_stars[i].m_z)) * hHeight + hHeight);

			if (x < 0 || x >= bitmap.getWidth() ||
				y < 0 || y >= bitmap.getHeight())
			{
				InitStar(i);
				continue;
			}
			triangleBuilderCounter++;
			if (triangleBuilderCounter == 1)
			{
				x1 = x;
				y1 = y;
			}
			else if (triangleBuilderCounter == 2)
			{
				x2 = x;
				y2 = y;
				//bitmap->DrawPixel(x, y, 0x00fd09ff);
				//bitmap.DrawPixel(x, y, color);
			}
			else if (triangleBuilderCounter == 3)
			{
				triangleBuilderCounter = 0;
					vertex v1(x1, y1), v2(x2, y2), v3(x, y);

					bitmap.FillTriangle(v1, v2, v3);
			}
		//	bitmap.FillTriangle(m_stars[0], m_stars[1], m_stars[2]);
		}
	}

}

void Stars3D::InitStar(int index)
{
	m_stars[index] = float4(
		2.f * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f) * m_spread,
		2.f * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f) * m_spread,
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread,
		1);
	/*
	m_starX[index] = 2.f * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f) * m_spread;
	m_starY[index] = 2.f * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f) * m_spread;
	m_starZ[index] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread;
	*/
}


Stars3D::~Stars3D()
{
}
