#include "Vec4.h"

namespace Greet{

	vec4::vec4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	vec4::vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float vec4::length()
	{
		return sqrt(x*x + y*y + z*z+ w*w);
	}

	vec4& vec4::add(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec4& vec4::subtract(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4& vec4::multiply(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	vec4& vec4::divide(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	bool vec4::compare(const vec4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	vec4& operator+(vec4& first, const vec4 &second)
	{
		return first.add(second);
	}

	vec4& operator-(vec4& first, const vec4 &second)
	{
		return first.subtract(second);
	}

	vec4& operator*(vec4& first, const vec4 &second)
	{
		return first.multiply(second);
	}

	vec4& operator/(vec4& first, const vec4 &second)
	{
		return first.divide(second);
	}

	vec4& vec4::operator+=(const vec4 &other)
	{
		return add(other);
	}

	vec4& vec4::operator-=(const vec4 &other)
	{
		return subtract(other);
	}

	vec4& vec4::operator*=(const vec4 &other)
	{
		return multiply(other);
	}

	vec4& vec4::operator/=(const vec4 &other)
	{
		return divide(other);
	}

	bool vec4::operator==(const vec4 &other)
	{
		return compare(other);
	}

	bool vec4::operator!=(const vec4 &other)
	{
		return !compare(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vec)
	{
		return stream << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.z;
	}
}