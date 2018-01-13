#include "Vec4.h"

namespace Greet{

	Vec4::Vec4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	Vec4::Vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Vec4::Length()
	{
		return sqrt(x*x + y*y + z*z+ w*w);
	}

	Vec4& Vec4::Add(const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vec4& Vec4::Subtract(const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vec4& Vec4::Multiply(const Vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vec4& Vec4::Divide(const Vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	bool Vec4::Compare(const Vec4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	Vec4& operator+(Vec4& first, const Vec4 &second)
	{
		return first.Add(second);
	}

	Vec4& operator-(Vec4& first, const Vec4 &second)
	{
		return first.Subtract(second);
	}

	Vec4& operator*(Vec4& first, const Vec4 &second)
	{
		return first.Multiply(second);
	}

	Vec4& operator/(Vec4& first, const Vec4 &second)
	{
		return first.Divide(second);
	}

	Vec4& Vec4::operator+=(const Vec4 &other)
	{
		return Add(other);
	}

	Vec4& Vec4::operator-=(const Vec4 &other)
	{
		return Subtract(other);
	}

	Vec4& Vec4::operator*=(const Vec4 &other)
	{
		return Multiply(other);
	}

	Vec4& Vec4::operator/=(const Vec4 &other)
	{
		return Divide(other);
	}

	bool Vec4::operator==(const Vec4 &other)
	{
		return Compare(other);
	}

	bool Vec4::operator!=(const Vec4 &other)
	{
		return !Compare(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4& vec)
	{
		return stream << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.z;
	}
}