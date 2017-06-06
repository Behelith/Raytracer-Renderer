#pragma once
#include "Bitmap.h"
#include "structures.h"
#include "vertex.h"

class vertex;

class RenderContext :
	public Bitmap
{
private:
	int *m_scanBuffer;
	void ScanConvertLIne(vertex a, vertex b, int side);
public:
	float * m_zbuffer;
	RenderContext(int width, int height);
	~RenderContext();
	void DrawScanBuffer(int yCoord, int xMin, int xMax);
	void ScanConvertTriangle(vertex a, vertex b, vertex c, int side);

	void FillShape(int yMin, int yMax);
	void FillTriangle(vertex a, vertex b, vertex c);
};

