#pragma once
#include "Animation.h"
#include "Character.h"
#include "Colors.h"

namespace CharacterLoads
{
	class Willy
	{
	public:
		void operator()(std::vector<Animation>& animations, Surface& surf, Color& chroma) const
		{
			animations.reserve(size_t(Character::Sequence::Count));
			for (int i = 0; i < 4; i++)
			{
				animations.emplace_back(Animation(90, 90 * i, 90, 90, 4, 0.15f, surf));
			}
			for (int i = 0; i < 4; i++)
			{
				animations.emplace_back(Animation(0, 90 * i, 90, 90, 1, 0.15f, surf));
			}
			chroma = Colors::Magenta;
		}
	private:
		
	};
	class Laura
	{
	public:
		void operator()(std::vector<Animation>& animations, Surface& surf, Color& chroma) const
		{
			animations.reserve(size_t(Character::Sequence::Count));
			for (int i = 0; i < 4; i++)
			{
				animations.emplace_back(Animation(0, 125 * (i % 2), 125, 125, 16, 0.06f, surf));
			}
			for (int i = 0; i < 4; i++)
			{
				animations.emplace_back(Animation(375, 125 * (i % 2), 125, 125, 1, 0.15f, surf));
			}
			std::reverse(animations[1].frames.begin(), animations[1].frames.end());
			chroma = Colors::White;
		}
	private:

	};
	class Umisan
	{
	public:
		void operator()(std::vector<Animation>& animations, Surface& surf, Color& chroma) const
		{
			animations.reserve(size_t(Character::Sequence::Count));
			//LRBF
			animations.emplace_back(Animation(0, 158  , 95, 158, 12, 0.05f, surf));
			animations.emplace_back(Animation(0, 2*158, 95, 158, 12, 0.05f, surf));
			animations.emplace_back(Animation(0, 3*158, 95, 158, 12, 0.05f, surf));
			animations.emplace_back(Animation(0, 0    , 95, 158, 12, 0.05f, surf));
			
			animations.emplace_back(Animation(3*158, 158  , 95, 158, 1, 0.15f, surf));
			animations.emplace_back(Animation(3*158, 2*158, 95, 158, 1, 0.15f, surf));
			animations.emplace_back(Animation(3*158, 3*158, 95, 158, 1, 0.15f, surf));
			animations.emplace_back(Animation(3*158, 0    , 95, 158, 1, 0.15f, surf));
			
			chroma = Colors::Magenta;
		}
	private:

	};
}