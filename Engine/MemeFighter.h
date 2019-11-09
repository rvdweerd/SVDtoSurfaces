#pragma once
#include "Character.h"
#include <memory>

class MemeFighter
{
public:
	~MemeFighter()
	{}
protected:
	MemeFighter(const std::string& name, std::unique_ptr<Character> pCharacter)//Character* pCharacter)
		:
		name(name)
		//,
		//character(std::move(pCharacter))
	{
		character = std::move(pCharacter);
	}

public:
	std::string name;
	//Character* character;
	std::unique_ptr<Character> character;
};

class MemeDwarf : public MemeFighter
{
public:
	template <typename C>
	MemeDwarf(const std::string& name, std::string fileName, C character, Vec2 startPos, BitmapText& bmtext)
		:
		MemeFighter(name, std::make_unique<Character>(fileName, character, startPos, bmtext))
	{
	}
	~MemeDwarf()
	{}
public:
};

class MemeHuman : public MemeFighter
{
public:
	template <typename C>
	MemeHuman(const std::string& name, std::string fileName, C character, Vec2 startPos, BitmapText& bmtext)
		:
		MemeFighter(name, std::make_unique<Character>(fileName, character, startPos, bmtext))
	{
	}
};