#include "Texture.h"
#include "iostream"

Texture::Texture()
{
	m_height = 0;
	m_width = 0;
}

Texture::Texture(const char* filename)
{

	clear(0);

	FIBITMAP *bm = FreeImage_Load(FIF_PNG, filename, PNG_DEFAULT);
	m_width = int(FreeImage_GetWidth(bm));
	m_height = int(FreeImage_GetHeight(bm));
	m_components = new unsigned int[m_width* m_height];

	//bm = FreeImage_Load(FIF_PNG, filename, PNG_DEFAULT);


	//if (bm)

	{    // 
		std::cout << "texture loaded!  " << endl;
		
		RGBQUAD color;

		for (int j = 0; j < m_height; j++)
		{
			for (int i = 0; i < m_width; i++)
			{
				Color c1(1.f, 1.f, 1.f);

				if (FreeImage_GetPixelColor(bm, i, m_height - j, &color))
				{}
				//		unsigned int tmp = Color(int(color.rgbRed), int(color.rgbGreen), int(color.rgbBlue)).toHex();
				m_components[i + j *m_width] = Color(int(color.rgbRed), int(color.rgbGreen), int(color.rgbBlue)).toHex();

			}
		}
		FreeImage_Unload(bm);
	}
}

void Texture::clear(unsigned color)
{
	std::fill(m_components, m_components + (m_width * m_height), color);
}

unsigned int * Texture::getComponents()
{
	return m_components;
}




Texture::~Texture()
{
}
