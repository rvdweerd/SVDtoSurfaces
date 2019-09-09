#include "BitmapText.h"
#include <assert.h>
#include "Colors.h"

BitmapText::BitmapText(Graphics& gfx)
	:
	gfx(gfx)
{
	for (int i = 0; i < (int)Font::Count; i++)
	{
		fontSpriteSheets.emplace_back(Surface(fontFiles[i]));
	}
}

RectI BitmapText::GetChar(char ch, Font font)
{
	int i = ch - ' ';
	int fontWidth = fontSizes[(int)font].x;
	int fontHeight = fontSizes[(int)font].y;
	assert(ch >= ' ');
	assert(ch <= ('~' + 1));
	return { { (i%32) * fontWidth , (i/32)* fontHeight},fontWidth,fontHeight };
}

void BitmapText::DrawChar(int x, int y, char ch, Font font)
{
	gfx.DrawSprite( x , y , GetChar(ch,font) , gfx.GetScreenRect() , fontSpriteSheets[int(font)] , true , Colors::White);
}

void BitmapText::DrawString(int x, int y, std::string str, Font font)
{
	int fontWidth = fontSizes[(int)font].x;
	int i = 0;
	for (char ch : str)
	{
		DrawChar(x + fontWidth *  i++  , y , ch , font);
	}
}
