#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>

class Character
{
public:
	template<typename C>
	Character(std::string fileName, C character, Vec2 startPos)
		:
		pos{ startPos },
		vel(0.0f, 1.0f),
		spriteSheet(Surface(fileName))
	{
		character(animations, spriteSheet, chroma);
	}
	void SetDirection(Vec2 dir);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void SetSpeedFactor(float factor) 
	{
		speedFactor = factor;
		if (factor > 1.01f)
		{
			distort = true;
		}
		else
		{
			distort = false;
		}
	}
	void ActivateHit()
	{
		hitActive = true;
		hitTime = hitDuration;
	}

public:
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
	Surface spriteSheet;
	Color chroma;
	std::vector<Animation> animations;
	Sequence sequence = Sequence::StandForward;
	float velocity = 140.0f;
	float speedFactor = 1.0f;
	bool distort = false;
	static constexpr float hitDuration = 0.045f;
	bool hitActive = false;
	float hitTime = 0.0f;
};
