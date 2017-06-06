#include "RenderContext.h"


RenderContext::RenderContext(int width, int height) : Bitmap (width, height)
{
	m_zbuffer = new float[width * height];
	fill(m_zbuffer, m_zbuffer + (width * height), INFINITY);


	m_scanBuffer = new int[height * 2];
}





RenderContext::~RenderContext()
{
	delete[] m_zbuffer;
}

void RenderContext::DrawScanBuffer(int yCoord, int xMin, int xMax)
{
	m_scanBuffer[yCoord * 2] = xMin;
	m_scanBuffer[yCoord * 2 + 1 ] = xMax;
}

void RenderContext::ScanConvertLIne(vertex a, vertex b, int side)
{
	//a - minY vert, b - maxY vert 
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
void RenderContext::ScanConvertTriangle(vertex a, vertex b, vertex c, int side)
{
	ScanConvertLIne(a, c, 0 + side);
	ScanConvertLIne(a, b, 1 - side);
	ScanConvertLIne(b, c, 1 - side);
}

void RenderContext::FillTriangle(vertex a, vertex b, vertex c)
{
	// a = min, b = mid, c = max *w dol*
	//float2 min = a, mid = b, max = c;

//	Matrix4 screenspaceTransform = Matrix4().InitScreenSpaceTransform(getWidth() / 2, getHeight() / 2);
	//vertex v1 = a.Transform(screenspaceTransform).PerspectiveDivide();
	//vertex v2 = b.Transform(screenspaceTransform).PerspectiveDivide();
	//vertex v3 = c.Transform(screenspaceTransform).PerspectiveDivide();
	vertex v1 = a;// .Transform(screenspaceTransform).PerspectiveDivide();
	vertex v2 = b;// .Transform(screenspaceTransform).PerspectiveDivide();
	vertex v3 = c;// .Transform(screenspaceTransform).PerspectiveDivide();
	

	if (v1.GetY() > v2.GetY())
	{
		vertex tmp = v2;
		v2 = v1;
		v1 = tmp;
	}
	if (v2.GetY() > v3.GetY())
	{
		vertex tmp = v3;
		v3 = v2;
		v2 = tmp;
	}
	if (v1.GetY() > v2.GetY())
	{
		vertex tmp = v2;
		v2 = v1;
		v1 = tmp;
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

 