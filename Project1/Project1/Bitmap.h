#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Color.h"

using namespace std;

class Bitmap
{
private:
	int m_width;
	int m_height;
	unsigned int * m_components;

public:
	Bitmap(int width, int height);
	virtual ~Bitmap();

	int getHeight();
	int getWidth();
	unsigned int * getComponents();

	void SaveAsTGA(string filename);

	void Clear(unsigned int color);
	void DrawPixel(int x, int y, unsigned int color);
};