#pragma once
#include "Willy.h"


void Willy::Draw(Graphics &gfx, Surface& surf, float dt)
{
	gfx.DrawSprite(pos.x, pos.y, frameRects[int(i)%5],surf);
	i += dt*speed/10;
}
