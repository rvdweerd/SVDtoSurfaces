#pragma once
#include "Character.h"
#include "Vec2.h"

Character::Character(Surface& surf)
	:
	pos{ 10,250 },
	vel(0.0f,1.0f),
	spriteSheet(surf)
{
	animations.reserve(size_t(Sequence::Count));
	for (int i = 0; i < 4; i++)
	{
		animations.emplace_back(Animation(90, 90*i , 90, 90, 4, 0.15f, surf));
	}
	for (int i = 0; i < 4; i++)
	{
		animations.emplace_back(Animation(0, 90*i , 90, 90, 1, 0.15f, surf));
	}
}

void Character::SetDirection(Vec2 dir)
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

void Character::Update(float dt)
{
	animations[ (int) sequence ].Update(dt);
	pos += vel * (speedFactor * dt);
	if (effectActive)
	{
		effectTime -= dt;
		if (effectTime < 0)
		{
			effectActive = false;
		}
	}
}

void Character::Draw(Graphics& gfx)
{
	if (distort || effectActive)
	{
		//animations[(int)sequence].DrawColor((Vei2)pos, gfx, Colors::Red );
		animations[(int)sequence].DrawTranslucent((Vei2)pos, gfx);
	}
	else
	{
		//animations[(int)sequence].Draw((Vei2)pos, gfx);
		animations[(int)sequence].DrawTranslucent((Vei2)pos, gfx);

	}
}

