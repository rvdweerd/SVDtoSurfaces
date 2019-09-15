#pragma once
#include <cmath>

template<typename T>
class Vec2_ 
{
public:
	Vec2_()
		:
		x(0),
		y(0)
	{
	}
	Vec2_(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{
	}
	Vec2_(Vec2_<float>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{
	}
	Vec2_ operator+(const Vec2_& rhs) const
	{
		return Vec2_(x + rhs.x, y + rhs.y);
	}
	Vec2_& operator+=(const Vec2_& rhs)
	{
		//x += rhs.x;
		//y += rhs.y;
		//return *this;
		return *this = *this + rhs;
	}
	Vec2_ operator-(const Vec2_& rhs) const
	{
		return Vec2_(x - rhs.x, y - rhs.y);
	}
	Vec2_& operator-=(const Vec2_& rhs)
	{
		return *this = *this - rhs;
	}
	Vec2_ operator*(const T rhs) const
	{
		return Vec2_( x*rhs, y*rhs);
	}
	//Vec2_ operator*(T lhs, const Vec2_& rhs)
	//{
	//	return Vec2_(lhs * rhs.x, lhs * rhs.y);
	//};
	Vec2_& operator*=(const T rhs)
	{
		return *this = *this * rhs;
	}
	T Length() const
	{
		//return std::sqrt(x*x+y*y);
		//return std::sqrt(this->LengthSq());
		return std::sqrt(LengthSq());
	}
	T LengthSq() const
	{
		return x * x + y * y;
	}
	Vec2_ GetNormalized() const
	{
		T len = Length();
		if (len == 0.0f)
		{
			return *this;
		}
		return *this * (1.0f / Length());
	}
	Vec2_& Normalize()
	{
		//return this->GetNormalized();
		//Vec2_ temp = GetNormalized();
		//return temp;
		return *this = GetNormalized();
	}
	/*Vec2_ operator-() const
	{
		return Vec2_(-x, -y);
	}*/
	bool operator==(Vec2_ rhs);
	bool operator!=(Vec2_ rhs);
	bool operator>(Vec2_ rhs);
	bool operator<(Vec2_ rhs);
	bool operator>=(Vec2_ rhs);
	bool operator<=(Vec2_ rhs);
	
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;