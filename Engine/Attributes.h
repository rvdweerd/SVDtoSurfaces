#pragma once
#include "Surface.h"
#include <vector>
#include "Vec2.h"
#include "SpriteEffect.h"
#include "BitmapText.h"

namespace IconLoads
{
	class Heart
	{
	public:
		void operator()(std::vector<Surface>& surf) const
		{
			for (int i = 0; i < 24; i++)
			{
				surf.emplace_back("bitmaps\\newFile" + std::to_string(i) + ".bmp");
			}
		}
	private:
	};
}

class Icon
{
public:
	template<typename C>
	Icon(C loadtype)
	{
		loadtype(iconFrames);
	}
	const Surface& GetFrame(int i) const
	{
		return iconFrames[i % iconFrames.size()];
	}
private:
	std::vector<Surface> iconFrames;
};

class Attributes
{
public:
	Attributes(int hp, BitmapText& bmtext)
		:
		health(hp),
		bmtext(bmtext)
	{}
	void Draw(const Vei2& pos, Graphics& gfx) const
	{
		health.Draw(pos, gfx);
		bmtext.DrawString(pos.x+25, pos.y, Colors::White, "[hp]"+std::to_string(health.GetHp()), BitmapText::Font::FixedSys8x14);
		//bmtext.DrawString(pos.x + 25, pos.y+20, Colors::White, std::to_string(sizeof bmtext), BitmapText::Font::Consolas13x24);
	}
	void TakeDamage(const int damage)
	{
		health.TakeDamage(damage);
	}
private:
	class Health
	{
	public:
		Health(int hp_start)
			:
			heart(IconLoads::Heart()),
			hp_max(hp_start),
			hp(hp_start)
		{
		}
		void Draw(const Vei2& pos,Graphics& gfx) const
		{
			gfx.DrawSprite(pos.x-15, pos.y-33, heart.GetFrame(int(23*hp/hp_max)), SpriteEffect::Ghost(Colors::Black));
			
		}
		const int GetHp() const
		{
			return hp;
		}
		void TakeDamage(const int damage)
		{
			if (--hp < 0)
			{
				hp = hp_max;
			}
		}
	private:
		Icon heart;
		int hp_max;
		int hp;
	};
	Health health;
	BitmapText& bmtext;
};