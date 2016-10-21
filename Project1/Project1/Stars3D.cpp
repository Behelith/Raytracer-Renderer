#include "Stars3D.h"

Stars3D::Stars3D(int number, float spread, float speed)
{
	m_speed = speed;
	m_spread = spread;
	m_number = number;

	m_starX = new float[number];
	m_starY = new float[number];
	m_starZ = new float[number];

	FOV = 40.0f;


	for (int i = 0; i < m_number; i++)
	{
		InitStar(i);
	}
}

void Stars3D::updateAndRender(RenderContext &bitmap, float delta, float fov)
{
	bitmap.Clear(0x120c0000);
	unsigned int color;
	int hWidth = bitmap.getWidth() / 2,
		hHeight = bitmap.getHeight() / 2;
	float pi180 = 3.14159265359f / 180.0f;
		// to radians: degrees * pi / 180
	//cout << tanHFOV << endl;
	
	float tanHFOV =(float)tan((fov * pi180) / 2.0f);//tanges (fov /2)

	for (int i = 0; i < m_number; i++)
	{

		int val = (int)(255 * m_starZ[i]);
		color = (val << 24 | val << 16);
		//cout << hex << color << endl;

		m_starZ[i] -= delta * m_speed;
		if (m_starZ[i] <= 0) InitStar(i);

		int x = (int)((m_starX[i] / (tanHFOV*m_starZ[i])) * hWidth + hWidth);
		int y = (int)((m_starY[i] / (tanHFOV*m_starZ[i]))* hHeight + hHeight);

		if (x < 0 || x >= bitmap.getWidth() ||
			y < 0 || y >= bitmap.getHeight())
		{
			InitStar(i);
		}
		else
		{
			//bitmap->DrawPixel(x, y, 0x00fd09ff);
			bitmap.DrawPixel(x, y, color);
		}
	}

}

void Stars3D::InitStar(int index)
{
	m_starX[index] = 2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread;
	m_starY[index] = 2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * m_spread;
	m_starZ[index] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + eps5) * m_spread;

}


Stars3D::~Stars3D()
{
}
