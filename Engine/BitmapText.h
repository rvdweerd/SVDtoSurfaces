#pragma once
#include <vector>
#include "Surface.h"
#include "Rect.h"
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
	void DrawChar(int x, int y, Color textColor, char ch, Font font);
	void DrawString(int x, int y, Color textColor, std::string str, Font font);

private:
	Graphics& gfx;
	std::vector<Surface> fontSpriteSheets;
	std::vector<std::string> fontFiles = { "bitmaps\\FixedSys16x28.bmp" , "bitmaps\\Consolas13x24.bmp" };
	std::vector<Vei2> fontSizes = { {16,28} , {13,24} };


};