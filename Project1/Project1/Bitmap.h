#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Texture.h"
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

	void draw(Texture texture);
	

	void SaveAsTGA(string filename);
	unsigned int getColorAt(int x, int y);

	void Clear(unsigned int color);
	void DrawPixel(int x, int y, unsigned int color);
};