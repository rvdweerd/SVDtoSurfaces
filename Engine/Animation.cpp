#pragma once
#include "Animation.h"
#include "Vec2.h"

Animation::Animation(int x, int y, int width, int height, int nFrames, Surface& surface)
	:
	sprites(surface)
{
	frames.reserve(nFrames);
	for (int n= 0; n < nFrames; n++)
	{
		Surface s(width, height);
		int nPixels = width * height;
		for (int i = 0; i < nPixels; i++)
		{
			s.PutPixel(i % width, i / width, surface.GetPixel(x + n*width + i % width, y + i / width));
		}
		frames.emplace_back(s);
	}
}


void Animation::Draw(Graphics& gfx, int x, int y) 
{
	//Surface s(frames[iCurrentFrame]);
	gfx.DrawSprite(x, y, frames[iCurrentFrame]);// , Colors::Magenta);
	
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
