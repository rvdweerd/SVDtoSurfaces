#include "Surface.h"
#include <cassert>

Surface::Surface(int width, int height)
	:
	pPixels(new Color[width*height]),
	width(width),
	height(height)
{
}

Surface::Surface(const Surface& source)
	:
	Surface(source.width, source.height)
{
	int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		this->pPixels[i] = source.pPixels[i];
	}
	//*this = source;
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

const Surface& Surface::operator=(const Surface& source)
{
	if (this != &source)
	{
		this->width = source.width;
		this->height = source.height;
		delete this->pPixels;
		this->pPixels = new Color[width*height];
		
		int nPixels = width * height;
		for (int i = 0; i < nPixels; i++)
		{
			this->pPixels[i] = source.pPixels[i];
		}
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[x + y * width] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[x+y*width];
}

int Surface::GetWidth()
{
	return width;
}

int Surface::GetHeight()
{
	return height;
}

/*void Surface::Draw(int x, int y, Graphics &gfx) const
{
	for (int i = 0; i < width * height; i++)
	{
		gfx.PutPixel(x + i % width, y + i / width, pPixels[i]);
	}
}*/
