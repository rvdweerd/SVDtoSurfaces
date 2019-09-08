#include "Character.h"

Character::Character(Surface& surf)
	:
	pos({10.0f,10.0f}),
	vel({1.0f,0}),
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
		sequence = Sequence::StandForward;
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
	animations[ (int) sequence ].Draw( gfx );
}

