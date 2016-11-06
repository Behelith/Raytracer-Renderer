#pragma once
#include "Bitmap.h"
#include "structures.h"

class RenderContext :
	public Bitmap
{
private:
	int *m_scanBuffer;
	void ScanConvertLIne(float2 a, float2 b, int side);
public:
	unsigned int * m_zbuffer;
	RenderContext(int width, int height);
	~RenderContext();
	void DrawScanBuffer(int yCoord, int xMin, int xMax);
	void ScanConvertTriangle(float2 a, float2 b, float2 c, int side);

	void FillShape(int yMin, int yMax);
	void FillTriangle(float2 a, float2 b, float2 c);
};

