#pragma once
#include "Surface.h"
#include <vector>
#include "Graphics.h"
class Animation
{
public:
	Animation(int x, int y, int width, int height, int nFrames, Surface& surface);
	void Draw(Graphics& gfx, int x, int y) ;
	void Update(float dt);
	void Advance();

public:
	Surface& sprites;
	std::vector<Surface> frames;
	int iCurrentFrame = 0;
	float holdTime = 0.2f;
	float currentFrameTime = 0.0f;

};