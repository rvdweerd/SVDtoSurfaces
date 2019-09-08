#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "Surface.h"

class Character
{
public:
	Character(Surface& surf);
	void SetDirection(Vec2 dir);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void SetSpeedFactor(float factor) {
		speedFactor = factor;
	}

private:
	enum class Sequence
	{
		WalkLeft,
		WalkRight,
		WalkBack,
		WalkForward,
		StandLeft,
		StandRight,
		StandBack,
		StandForward,
		Count
	};
private:
	Vec2 pos;
	Vec2 vel;
	Surface& spriteSheet;
	std::vector<Animation> animations;
	Sequence sequence = Sequence::StandForward;
	float velocity = 200.0f;
	float speedFactor = 1.0f;

};
