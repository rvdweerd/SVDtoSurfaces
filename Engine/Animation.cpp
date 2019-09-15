#pragma once
#include "Animation.h"
#include "Vec2.h"
#include "Rect.h"

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
