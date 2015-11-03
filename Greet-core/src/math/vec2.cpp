#include "vec2.h"

namespace greet{
	namespace math{

	vec2::vec2()
	{
		this->x = 0;
		this->y = 0;
	}

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float vec2::length()
	{
		return sqrt(x*x + y*y);
	}

	float vec2::lengthSQ()
	{
		return x*x + y*y;
	}

	vec2& vec2::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		return *this;
	}

	vec2& vec2::rotate(const float deg)
	{
		float rad = toRadians(deg);
		float c = cos(rad);
		float s = sin(rad);

		float tempX = x*c - y*s;
		float tempY = x*s + y*c;
		x = tempX;
		y = tempY;

		return *this;
	}


	vec2& vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	bool vec2::compare(const vec2& other)
	{
		return x == other.x && y == other.y;
	}

	std::ostream& operator<<(std::ostream& stream, const vec2 &vec)
	{
		stream << "vec2(" << vec.x << ", " << vec.y << ")";
		return stream;
	}

	vec2 operator+(const vec2& first, const vec2 &second)
	{
		return vec2(first.x,first.y).add(second);
	}

	vec2 operator-(const vec2& first, const vec2 &second)
	{
		return vec2(first.x, first.y).subtract(second);
	}

	vec2 operator*(const vec2& first, const vec2 &second)
	{
		return vec2(first.x, first.y).multiply(second);
	}

	vec2 operator/(const vec2& first, const vec2 &second)
	{
		return vec2(first.x, first.y).divide(second);
	}

	vec2 operator+(const vec2& first, const float c)
	{
		return vec2(first.x+c, first.y+c);
	}

	vec2 operator-(const vec2& first, const float c)
	{
		return vec2(first.x-c, first.y-c);
	}

	vec2 operator*(const vec2&  first, const float c)
	{
		return vec2(first.x*c,first.y*c);
	}

	vec2 operator/(const vec2& first, const float c)
	{
		return vec2(first.x/c, first.y/c);
	}

	vec2& vec2::operator+=(const vec2 &other)
	{
		return add(other);
	}

	vec2& vec2::operator-=(const vec2 &other)
	{
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2 &other)
	{
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2 &other)
	{
		return divide(other);
	}

	vec2& vec2::operator+=(const float other)
	{
		x += other;
		y += other;
		return *this;
	}

	vec2& vec2::operator-=(const float other)
	{
		x -= other;
		y -= other;
		return *this;
	}

	vec2& vec2::operator*=(const float other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	vec2& vec2::operator/=(const float other)
	{
		x /= other;
		y /= other;
		return *this;
	}

	bool vec2::operator==(const vec2 &other)
	{
		return compare(other);
	}

	bool vec2::operator!=(const vec2 &other)
	{
		return !compare(other);
	}
}}