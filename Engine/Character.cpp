#pragma once
#include "Character.h"
#include "Vec2.h"
#include "SpriteEffect.h"
//#include "CharacterLoads.h"

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
	if (hitActive)
	{
		hitTime -= dt;
		if (hitTime < 0)
		{
			hitActive = false;
		}
	}
	//attributes.TakeDamage(1);
}

void Character::Draw(Graphics& gfx)
{
	SpriteEffect::Ghost effectGhost{ chroma };
	SpriteEffect::Substitution effectSubst{ chroma , Colors::Red };
	SpriteEffect::SubstitutionGhost effectSubGhost{ chroma , Colors::Red };
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
		animations[(int)sequence].Draw((Vei2)pos, gfx, effectGhost);//SpriteEffect::Copy());

	}
	attributes.Draw(Vei2(pos)+pos2topLeft,gfx);
	if (active)
	{
		gfx.DrawRect(GetPersonalSpace(), Colors::Red);
	}
	else
	{
		gfx.DrawRect(GetPersonalSpace(), Colors::Blue);
	}
	
}

