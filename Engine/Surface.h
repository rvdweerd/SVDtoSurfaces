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
private:
	std::vector<Color> pixels;
	int width;
	int height;
};