#include "BitmapText.h"
#include <assert.h>
#include "Colors.h"
#include "SpriteEffect.h"

BitmapText::BitmapText(Graphics& gfx)
	:
	gfx(gfx)
{
	//for (int i = 0; i < (int)Font::Count; i++)
	//{
	//	fontSpriteSheets.emplace_back(Surface(fontFiles[i]));
	//}
	fontSpriteSheets.emplace_back(Surface(fontFiles[0]));
	fontSpriteSheets.emplace_back(Surface(fontFiles[0]),0.5f);
	fontSpriteSheets.emplace_back(Surface(fontFiles[1]));
	fontSpriteSheets.emplace_back(Surface(fontFiles[1]), 0.5f);
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

void BitmapText::DrawChar(int x, int y, Color textColor, char ch, Font font)
{
	// create effect functor
	SpriteEffect::Substitution e{ Colors::White, textColor };
	// draw the character
	gfx.DrawSprite( x , y , GetChar(ch,font) , gfx.GetScreenRect() , fontSpriteSheets[int(font)] , e);
}

void BitmapText::DrawString(int x, int y, Color textColor, std::string str, Font font)
{
	int fontWidth = fontSizes[(int)font].x;
	int i = 0;
	for (char ch : str)
	{
		DrawChar(x + fontWidth *  i++  , y , textColor, ch , font);
	}
}
