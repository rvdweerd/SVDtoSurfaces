#pragma once
#include "Character.h"

class MemeFighter
{
public:
	~MemeFighter()
	{}
protected:
	MemeFighter(const std::string& name, Character* pCharacter)
		:
		name(name),
		character(pCharacter)
	{}

public:
	std::string name;
	Character* character;
};

class MemeDwarf : public MemeFighter
{
public:
	template <typename C>
	MemeDwarf(const std::string& name, std::string fileName, C character, Vec2 startPos, BitmapText& bmtext)
		:
		MemeFighter(name, new Character(fileName, character, startPos, bmtext))
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
		MemeFighter(name, new Character(fileName, character, startPos, bmtext))
	{
	}
};