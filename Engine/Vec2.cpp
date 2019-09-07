#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
	:
	x(0),
	y(0)
{
}

Vec2::Vec2(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs) 
{
	//x += rhs.x;
	//y += rhs.y;
	//return *this;
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(const float k) const
{
	return Vec2(k*x,k*y);
}

Vec2 operator*(float lhs, const Vec2& rhs)
{
	return Vec2(lhs * rhs.x, lhs * rhs.y);
};

Vec2& Vec2::operator*=(const float k)
{
	return *this = *this*k;
}

float Vec2::Length() const
{
	//return std::sqrt(x*x+y*y);
	//return std::sqrt(this->LengthSq());
	return std::sqrt(LengthSq());
}

float Vec2::LengthSq() const
{
	return x*x+y*y;
}

Vec2 Vec2::GetNormalized() const
{
	float len = Length();
	if (len == 0.0f)
	{
		return *this;
	}
	return *this * (1.0f / Length() );
}

Vec2& Vec2::Normalize()
{
	//return this->GetNormalized();
	//Vec2 temp = GetNormalized();
	//return temp;
	return *this = GetNormalized();
}

/*Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}*/


