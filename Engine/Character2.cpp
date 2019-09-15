#pragma once
#include "Character2.h"
#include "Vec2.h"
#include "SpriteEffect.h"
#include <algorithm>

Character2::Character2(Surface& surf)
	:
	pos{ 10,250 },
	vel(0.0f,1.0f),
	spriteSheet(surf)
{
	animations.reserve(size_t(Sequence::Count));
	for (int i = 0; i < 4; i++)
	{
		animations.emplace_back(Animation(0, 125*(i%2) , 125, 125, 16, 0.04f, surf));
	}
	for (int i = 0; i < 4; i++)
	{
		animations.emplace_back(Animation(375, 125*(i%2) , 125, 125, 1, 0.15f, surf));
	}
	std::reverse(animations[1].frames.begin(), animations[1].frames.end());
}

void Character2::SetDirection(Vec2 dir)
{
	if (dir.x > 0)
	{
		sequence = Sequence::WalkRight;
	}
	else if (dir.x < 0)
	{
		sequence = Sequence::WalkLeft;
	}
	else if (dir.y > 0)
	{
		sequence = Sequence::WalkForward;
	}
	else if (dir.y < 0)
	{
		sequence = Sequence::WalkBack;
	}
	else
	{
		if (vel.y>0)
		{
			sequence = Sequence::StandForward;
		}
		else if (vel.y < 0)
		{
			sequence = Sequence::StandBack;
		}
		else if (vel.x > 0)
		{
			sequence = Sequence::StandRight;
		}
		else if (vel.x < 0)
		{
			sequence = Sequence::StandLeft;
		}
	}
	vel = dir * velocity;
}

void Character2::Update(float dt)
{
	animations[ (int) sequence ].Update(dt);
	pos += vel * (speedFactor * dt);
	if (hitActive)
	{
		hitTime -= dt;
		if (hitTime < 0)
		{
			hitActive = false;
		}
	}
}

void Character2::Draw(Graphics& gfx)
{
	SpriteEffect::Ghost effectGhost{ Colors::White };
	SpriteEffect::Substitution effectSubst{ Colors::White , Colors::Red };
	SpriteEffect::SubstitutionGhost effectSubGhost{ Colors::White , Colors::Red };
	if (hitActive)
	{
		animations[(int)sequence].Draw((Vei2)pos, gfx, effectSubst);
	}
	else if (distort)
	{
		animations[(int)sequence].Draw((Vei2)pos, gfx, effectSubGhost);
	}
	else
	{
		animations[(int)sequence].Draw((Vei2)pos, gfx, effectGhost);
	}
}

