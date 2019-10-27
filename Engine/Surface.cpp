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
Surface::Surface(const Surface& sourceSurface, float scaling)
	:
	pPixels( new Color[ int( sourceSurface.GetWidth()*scaling * sourceSurface.GetHeight()*scaling) ] ),
	width(int(sourceSurface.GetWidth()* scaling)),
	height(int(sourceSurface.GetHeight()* scaling))
{
	float f = 1 / scaling;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int R = 0; int G = 0; int B = 0;
			for (int y_orig = int(y * f); y_orig < int((y + 1) * f); y_orig++)
			{
				for (int x_orig = int(x * f); x_orig<int((x + 1) * f); x_orig++)
				{
					R += sourceSurface.GetPixel(x_orig, y_orig).GetR();
					G += sourceSurface.GetPixel(x_orig, y_orig).GetG();
					B += sourceSurface.GetPixel(x_orig, y_orig).GetB();
				}
			}
			PutPixel(x, y, Color(char(R / f / f), char(G / f / f), char(B / f / f)));
		}
	}
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
			if (bmInfoHeader.biBitCount == 24)
			{
				file.seekg(padding, std::ios_base::cur);
			}
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

void Surface::Scale(const float scaling)
{
	if (scaling<0.999f)
	{
		int scalingI = 2;
		int width_new = int(GetWidth() / scalingI);
		int height_new = int(GetHeight() / scalingI);
		Color* pNew = new Color[int(GetWidth() / scalingI * GetHeight() / scalingI)];
		for (int y = 0; y < height_new; y++)
		{
			for (int x = 0; x < width_new; x++)
			{
				int R = 0; int G = 0; int B = 0;
				for (int y_orig = int(y * scalingI); y_orig < int((y + 1) * scalingI); y_orig++)
				{
					for (int x_orig = int(x * scalingI); x_orig<int((x + 1) * scalingI); x_orig++)
					{
						R += GetPixel(x_orig, y_orig).GetR();
						G += GetPixel(x_orig, y_orig).GetG();
						B += GetPixel(x_orig, y_orig).GetB();
					}
				}
				//PutPixel(x, y, Color(char(R / f / f), char(G / f / f), char(B / f / f)));
				pNew[x + y * width_new] = Color(char(R / scalingI/scalingI), char(G / scalingI / scalingI), char(B / scalingI / scalingI));
			}
		}
		delete pPixels;
		pPixels = pNew;
		pNew = nullptr;
		width = width_new;
		height = height_new;
	}
	else if (scaling > 1.001f)
	{
		//float f = 1 / scaling;
		int scalingI = 2;
		int width_new = int(GetWidth() * scalingI);
		int height_new = int(GetHeight() * scalingI);
		Color* pNew = new Color[int(GetWidth() * scalingI * GetHeight() * scalingI)];
		for (int y_orig = 0; y_orig < GetHeight(); y_orig++)
		{
			for (int x_orig = 0; x_orig < GetWidth(); x_orig++)
			{
				for (int x = 0; x < scalingI; x++)
				{
					for (int y = 0; y < scalingI; y++)
					{
						pNew[(x_orig*scalingI+x) + (y_orig*scalingI+y) * width_new] = GetPixel(x_orig,y_orig);
					}
				}


			}
		}
		delete pPixels;
		pPixels = pNew;
		pNew = nullptr;
		width = width_new;
		height = height_new;
	}
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

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return { {0,0},width, height};
}



