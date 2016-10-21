#include "RenderContext.h"


void RenderContext::ScanConvertLIne(float2 a, float2 b, int side)
{
	int yStart = (int)a.GetY(),
	yEnd = (int)b.GetY(),
	xStart = (int)a.GetX(),
	xEnd = (int)b.GetX();

	int yDistance = yEnd - yStart;
	int XDistance = xEnd - xStart;

	if (yDistance <= 0) return;

	float xStep = (float)XDistance / (float)yDistance;
	float currentX = xStart;

	for (int j = yStart; j < yEnd; j++)
	{
		m_scanBuffer[j * 2 + side] = (int)currentX;
			currentX += xStep;
	}

}

RenderContext::RenderContext(int width, int height) : Bitmap (width, height)
{
	m_scanBuffer = new int[height * 2];
}


RenderContext::~RenderContext()
{
}

void RenderContext::DrawScanBuffer(int yCoord, int xMin, int xMax)
{
	m_scanBuffer[yCoord * 2] = xMin;
	m_scanBuffer[yCoord * 2 +1 ] = xMax;
}

void RenderContext::ScanConvertTriangle(float2 a, float2 b, float2 c, int side)
{
	ScanConvertLIne(a, c, 0 + side);
	ScanConvertLIne(a, b, 1 - side);
	ScanConvertLIne(b, c, 1 - side);



}

void RenderContext::FillTriangle(float2 a, float2 b, float2 c)
{
	// a = min, b = mid, c = max *w dol*
	//float2 min = a, mid = b, max = c;
	
	if (a.GetY() > a.GetY())
	{
		float2 tmp = b;
		b = a;
		a = tmp;
	}
	if (b.GetY() > c.GetY())
	{
		float2 tmp = c;
		c = b;
		b = tmp;
	}
	if (a.GetY() > b.GetY())
	{
		float2 tmp = b;
		b = a;
		a = tmp;
	}

	float area = a.TriangleArea(c, b);
	int side = area >= 0 ? 1 : 0;

	ScanConvertTriangle(a, b, c, side);
	FillShape(a.GetY(), c.GetY());
}

void RenderContext::FillShape(int yMin, int yMax)
{
	for (int j = yMin; j < yMax; j++)
	{
		int xMin = m_scanBuffer[j * 2];
		int xMax = m_scanBuffer[j * 2 +1];

		for (int i = xMin; i < xMax; i++)
		{
			DrawPixel(i, j, 0xff000000);
		}
		//cout << "Sd" << endl; 

	}
}

