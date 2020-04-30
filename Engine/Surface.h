#pragma once
#include "Colors.h"
#include <string>
#include "Rect.h"
#include <memory>
#include <vector>

class Surface
{
public:
	Surface(int width, int height);
	Surface(const std::string& fileName);
	Surface(const Surface& sourceSurface, float scaling);
	Surface(const Surface&);
	Surface(Surface&&) = default;
	const Surface& operator=(const Surface&);
	Surface& operator=(Surface&&) = default;
	void Scale(const float scaling);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;  
	void Clip()
	{
		std::vector<std::vector<Color>> tmp(90,std::vector<Color>(90,0));

		int s = 90;
		for (int y = 0; y < 90; y++)
		{
			for (int x = 0; x < 90; x++)
			{
				tmp[y][x] = pixels[y * width + x];
			}
		}
		pixels.clear();
		width = 90;
		height = 90;
		for (int y = 0; y < 90; y++)
		{
			for (int x = 0; x < 90; x++)
			{
				pixels.push_back(tmp[y][x]);
			}
		}
	}
private:
	std::vector<Color> pixels;
	int width;
	int height;
};