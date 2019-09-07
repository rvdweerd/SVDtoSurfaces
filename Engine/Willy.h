#pragma once
#include "Vec2.h"
#include <vector>
#include "RectI.h"
#include "Graphics.h"
#include "Surface.h"
class Willy
{
public:
	void Draw(Graphics &gfx, Surface& surf, float dt);

public:
	float speed = 50.0f; //pixel/s
	Vec2 pos{ 0,0 };
	std::vector<RectI> frameRects{ {{0,90},90,90}, {{90,90},90,90}, {{180,90},90,90}, {{270,90},90,90}, {{360,90},90,90} };
	float i = 0;
};