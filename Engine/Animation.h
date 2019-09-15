#pragma once
#include "Surface.h"
#include <vector>
#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"
#include "SpriteEffect.h"

class Animation
{
public:
	Animation(int x, int y, int width, int height, int nFrames, float hTime, Surface& spriteSheet_in);
	template <typename E>
	void Draw(Vei2 pos, Graphics& gfx, E effect) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurrentFrame], spriteSheet, effect);
	}
	//void Draw(Vei2 pos, Graphics& gfx,const RectI clip) const;
	void Update(float dt);
	void Advance();

public:
	Surface& spriteSheet;
	std::vector<RectI> frames;
	int iCurrentFrame = 0;
	float holdTime = 0.15f;
	float currentFrameTime = 0.0f;

};