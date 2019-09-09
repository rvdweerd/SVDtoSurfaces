#pragma once
#include <vector>
#include "Surface.h"
#include "RectI.h"
#include "Graphics.h"
#include <string>

class BitmapText
{
public:
	enum class Font
	{
		FixedSys16x28=0,
		Consolas13x24,
		Count
	};

public:
	BitmapText(Graphics& gfx);
	RectI GetChar(char ch, Font font);
	void DrawChar(int x, int y, char ch, Font font);
	void DrawString(int x, int y, std::string str, Font font);

private:
	Graphics& gfx;
	std::vector<Surface> fontSpriteSheets;
	std::vector<std::string> fontFiles = { "bitmaps\\FixedSys16x28.bmp" , "bitmaps\\Consolas13x24.bmp" };
	std::vector<Vei2> fontSizes = { {16,28} , {13,24} };


};