#pragma once
#include "Animation.h"
#include "Vec2.h"
#include "RectI.h"

Animation::Animation(int x, int y, int width, int height, int nFrames, float hTime, Surface& spriteSheet_in)
	:
	holdTime(hTime),
	spriteSheet(spriteSheet_in)
{
	frames.reserve(nFrames);
	for (int n= 0; n < nFrames; n++)
	{
		frames.emplace_back( RectI( { x + n*width, y }, width, height ) );
	}
}

void Animation::Draw(Vei2 pos, Graphics& gfx) const
{
	gfx.DrawSprite( pos.x,pos.y, frames[iCurrentFrame],  spriteSheet, Colors::Magenta);
}

void Animation::DrawColor(Vei2 pos, Graphics& gfx, Color color) const
{
	gfx.DrawSpriteSubstitute(pos.x, pos.y, color, frames[iCurrentFrame], spriteSheet, Colors::Magenta);
}

void Animation::Draw(Vei2 pos, Graphics& gfx, const RectI clip) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurrentFrame], clip, spriteSheet, Colors::Magenta);
}

void Animation::Update(float dt)
{
	currentFrameTime += dt;
	if (currentFrameTime > holdTime)
	{
		Advance();
		currentFrameTime = 0;
	}
}

void Animation::Advance()
{
	if (++iCurrentFrame >= frames.size())
	{
		iCurrentFrame = 0;
	}
	
}
