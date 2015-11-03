#include "vec3.h"

namespace greet{
	namespace math{

	vec3::vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float vec3::length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	vec3& vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	bool vec3::compare(const vec3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3 &vec)
	{
		stream << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return stream;
	}

	vec3& operator+(vec3 first, const vec3 &second)
	{
		return first.add(second);
	}

	vec3& operator-(vec3 first, const vec3 &second)
	{
		return first.subtract(second);
	}

	vec3& operator*(vec3 first, const vec3 &second)
	{
		return first.multiply(second);
	}

	vec3& operator/(vec3 first, const vec3 &second)
	{
		return first.divide(second);
	}

	vec3& vec3::operator+=(const vec3 &other)
	{
		return add(other);
	}

	vec3& vec3::operator-=(const vec3 &other)
	{
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3 &other)
	{
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3 &other)
	{
		return divide(other);
	}

	bool vec3::operator==(const vec3 &other)
	{
		return compare(other);
	}

	bool vec3::operator!=(const vec3 &other)
	{
		return !compare(other);
	}
}}