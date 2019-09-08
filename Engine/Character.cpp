#include "Character.h"

Character::Character(Surface& surf)
	:
	pos({10,10}),
	vel({1.0,0}),
	sprites(surf)
{
	animations.reserve(size_t(Sequence::Count));
	animations.emplace_back(Animation(90, 0, 90, 90, 4, sprites));
	animations.emplace_back(Animation(90, 90, 90, 90, 4, sprites));
	animations.emplace_back(Animation(90, 180, 90, 90, 4, sprites));
	animations.emplace_back(Animation(90, 270, 90, 90, 4, sprites));
	animations.emplace_back(Animation(0, 0, 90, 90, 1, sprites));
	animations.emplace_back(Animation(0, 90, 90, 90, 1, sprites));
	animations.emplace_back(Animation(0, 180, 90, 90, 1, sprites));
	animations.emplace_back(Animation(0, 270, 90, 90, 1, sprites));
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
	pos += vel * dt;
}


void Character::Draw(Graphics& gfx)
{
	animations[ (int) sequence ].Draw( gfx, (Vei2) pos );
}

