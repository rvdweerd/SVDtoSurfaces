#pragma once
#include "Colors.h"
//#include "Graphics.h"

class Surface
{
public:
	Surface(int width, int height);
	Surface(const Surface&);
	~Surface();
	const Surface& operator=(const Surface&);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth();
	int GetHeight();
//	void Draw(int x, int y, Graphics& gfx) const;
	   
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};