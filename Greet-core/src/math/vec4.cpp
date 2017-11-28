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

	float vec4::Length()
	{
		return sqrt(x*x + y*y + z*z+ w*w);
	}

	vec4& vec4::Add(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec4& vec4::Subtract(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4& vec4::Multiply(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	vec4& vec4::Divide(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	bool vec4::Compare(const vec4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	vec4& operator+(vec4& first, const vec4 &second)
	{
		return first.Add(second);
	}

	vec4& operator-(vec4& first, const vec4 &second)
	{
		return first.Subtract(second);
	}

	vec4& operator*(vec4& first, const vec4 &second)
	{
		return first.Multiply(second);
	}

	vec4& operator/(vec4& first, const vec4 &second)
	{
		return first.Divide(second);
	}

	vec4& vec4::operator+=(const vec4 &other)
	{
		return Add(other);
	}

	vec4& vec4::operator-=(const vec4 &other)
	{
		return Subtract(other);
	}

	vec4& vec4::operator*=(const vec4 &other)
	{
		return Multiply(other);
	}

	vec4& vec4::operator/=(const vec4 &other)
	{
		return Divide(other);
	}

	bool vec4::operator==(const vec4 &other)
	{
		return Compare(other);
	}

	bool vec4::operator!=(const vec4 &other)
	{
		return !Compare(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vec)
	{
		return stream << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.z;
	}
}