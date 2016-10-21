#include "Bitmap.h"




Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height)
{
	m_components = new unsigned int[width * height];
	Clear(0x00);
}

void Bitmap::Clear(unsigned int color)
{
	fill(m_components, m_components + (m_width * m_height), color);
}

void Bitmap::DrawPixel(int x, int y, unsigned int color)
{
	// (nr wiersza )+ nr kolumny * szerokosc obrazu
	m_components[x + y *m_width] = color;
}

unsigned int * Bitmap::getComponents()
{
	return m_components;
}


void Bitmap::SaveAsTGA(string filename)
{
	//Error checking
	if (m_width <= 0 || m_height <= 0)
	{
		cout << "Image size is not set properly" << endl;
		return;
	}

	ofstream o(filename.c_str(), ios::out | ios::binary);

	//Write the header
	o.put(0);
	o.put(0);
	o.put(2);                         /* uncompressed RGB */
	o.put(0); 		o.put(0);
	o.put(0); 	o.put(0);
	o.put(0);
	o.put(0); 	o.put(0);           /* X origin */
	o.put(0); 	o.put(0);           /* y origin */
	o.put((m_width & 0x00FF));
	o.put((m_width & 0xFF00) / 256);
	o.put((m_height & 0x00FF));
	o.put((m_height & 0xFF00) / 256);
	o.put(32);                        /* 24 bit bitmap */
	o.put(0);

	//Write the pixel data
	for (int j = m_height-1;j >= 0 ; j--) 
	{
		for (int i = 0;i < m_width;i++)
		{
			o.put(Color::bToInt(m_components[i + j*m_width]));
			o.put(Color::gToInt(m_components[i + j*m_width]));
			o.put(Color::rToInt(m_components[i + j*m_width]));
			o.put(Color::aToInt(m_components[i + j*m_width]));
		}
	}
/*
	for (int i = 0;i<m_height*m_width;i++) {
		o.put(Color::getB(m_components[i]));
		o.put(Color::getG(m_components[i]));
		o.put(Color::getR(m_components[i]));
		o.put(Color::getA(m_components[i]));
	}
		
	for (int i = 0;i<m_height*m_width;i++) {
		o.put(Color::getB(tmpTab[i]));
		o.put(Color::getG(tmpTab[i]));
		o.put(Color::getR(tmpTab[i]));
		o.put(Color::getA(tmpTab[i]));
	}
*/
	//close the file
	o.close();

}


int Bitmap::getHeight() { return m_height; }

int Bitmap::getWidth() { return m_width; }

Bitmap::~Bitmap()
{
	delete[] m_components;
}
