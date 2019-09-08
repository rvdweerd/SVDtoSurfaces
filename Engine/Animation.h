#pragma once
#include "Surface.h"
#include <vector>
#include "Graphics.h"
#include "Vec2.h"
#include "RectI.h"

class Animation
{
public:
	Animation(int x, int y, int width, int height, int nFrames, float hTime);
	void Draw(Vei2 pos, Graphics& gfx, Surface& surface);
	void Update(float dt);
	void Advance();

public:
	//Surface& sprites;
	std::vector<RectI> frames;
	int iCurrentFrame = 0;
	float holdTime = 0.15f;
	float currentFrameTime = 0.0f;

};