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
	Surface& sprites;
	std::vector<Animation> animations;
	Sequence sequence = Sequence::StandForward;
	float velocity = 60.0f;


};
