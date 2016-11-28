#pragma once
#include <string>
#include "FreeImage.h"
#include "Color.h"

class Texture
{
private:
	int m_width;
	int m_height;
	unsigned int *m_components;

public:
	Texture(const char * filename);
	Texture();
	~Texture();
	void clear(unsigned int color);

	unsigned int * getComponents();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
};

