#pragma once
#include "Character.h"
#include "Vec2.h"

Character::Character(Surface& surf)
	:
	pos({10,10}),
	vel({1.0,0}),
	spriteSheet(surf)
{
	animations.reserve(size_t(Sequence::Count));
	animations.emplace_back(Animation(90, 0  , 90, 90, 4, 0.15f));
	animations.emplace_back(Animation(90, 90 , 90, 90, 4, 0.15f));
	animations.emplace_back(Animation(90, 180, 90, 90, 4, 0.15f));
	animations.emplace_back(Animation(90, 270, 90, 90, 4, 0.15f));
	animations.emplace_back(Animation(0,  0  , 90, 90, 1, 0.15f));
	animations.emplace_back(Animation(0,  90 , 90, 90, 1, 0.15f));
	animations.emplace_back(Animation(0,  180, 90, 90, 1, 0.15f));
	animations.emplace_back(Animation(0,  270, 90, 90, 1, 0.15f));
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
	vel = velocity * dir;
}

void Character::Update(float dt)
{
	animations[ (int) sequence ].Update(dt);
	pos += speedFactor * vel * dt;
}


void Character::Draw(Graphics& gfx)
{
	//Vei2 posInt{ (int)pos.x , (int)pos.y };
	animations[ (int) sequence ].Draw( (Vei2)pos, gfx, spriteSheet);
}

