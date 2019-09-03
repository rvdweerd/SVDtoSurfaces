#include "Surface.h"
#include <cassert>
#include "ChiliWin.h"
#include <fstream>

Surface::Surface(int width, int height)
	:
	pPixels(new Color[width*height]),
	width(width),
	height(height)
{
}

Surface::Surface(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof bmFileHeader);
	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof bmInfoHeader);
	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;
	
	pPixels = new Color[width * std::abs(height) ];
	file.seekg( bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;
	bool topToBottom = true;
	if (height < 0)
	{
		topToBottom = false;
		height = -height;
	}
	{
		for (int y = 0; y < height ; y++)
		{
			for (int x = 0; x < width; x++)
			{
				unsigned char b;
				file.read(reinterpret_cast<char*>(&b), 1);
				unsigned char g;
				file.read(reinterpret_cast<char*>(&g), 1);
				unsigned char r;
				file.read(reinterpret_cast<char*>(&r), 1);
				if (bmInfoHeader.biBitCount == 32)
				{
					file.seekg(1, std::ios::cur);
				}
				if (topToBottom)
				{
					PutPixel(x, (height - 1) - y, Color(r, g, b));
				}
				else
				{
					PutPixel(x, y , Color(r, g, b));
				}
			}
			file.seekg(padding, std::ios_base::cur);
		}
	}
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
