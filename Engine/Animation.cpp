#pragma once
#include "Animation.h"
#include "Vec2.h"
#include "RectI.h"

Animation::Animation(int x, int y, int width, int height, int nFrames, float hTime)
	:
	holdTime(hTime)
{
	frames.reserve(nFrames);
	for (int n= 0; n < nFrames; n++)
	{
		frames.emplace_back( RectI( { x + n*width, y }, width, height ) );
	}
}

void Animation::Draw(Vei2 pos, Graphics& gfx, Surface& surface)
{
	gfx.DrawSprite( pos.x,pos.y, frames[iCurrentFrame],  surface, Colors::Magenta);
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
