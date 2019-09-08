#pragma once
#include "Vei2.h"
class Vec2 
{
public:
	Vec2();
	Vec2(float x_in , float y_in);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2 & rhs);
	Vec2 operator*(const float k) const;
	friend Vec2 operator*(float lhs, const Vec2& rhs);
	Vec2& operator*=(const float k);
	explicit operator Vei2() const;

	float Length() const;
	float LengthSq() const;

	Vec2 GetNormalized() const; //returns normalized vector
	Vec2& Normalize(); //changes vector to normalized (same as void Normalize())

	bool operator==(Vec2 rhs);
	bool operator!=(Vec2 rhs);
	bool operator>(Vec2 rhs);
	bool operator<(Vec2 rhs);
	bool operator>=(Vec2 rhs);
	bool operator<=(Vec2 rhs);
	
public:
	float x;
	float y;

};