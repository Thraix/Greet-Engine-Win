#include "Vec3.h"

#include "MathFunc.h"
#include "Maths.h"

namespace Greet{

	vec3::vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float vec3::length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	float vec3::dot(const vec3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	vec3 vec3::cross(const vec3& vec) const
	{
		float x_ = y * vec.z - z * vec.y;
		float y_ = z * vec.x - x * vec.z;
		float z_ = x * vec.y - y * vec.x;
		return vec3(x_, y_, z_);
	}

	vec3& vec3::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	vec3& vec3::rotate(const float& angle, const vec3& axis)
	{
		float sh = (float)sin(Math::toRadians(angle / 2.0));
		float ch = (float)cos(Math::toRadians(angle / 2.0));

		float rX = axis.x * sh;
		float rY = axis.y * sh;
		float rZ = axis.z * sh;
		float rW = ch;

		quaternion rotation(rX,rY,rZ,rW);
		quaternion conjugate = rotation.conjugate();

		quaternion w = rotation * (*this) * conjugate;

		x = w.x;
		y = w.y;
		z = w.z;

		return *this;
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

	vec3& vec3::add(const float c)
	{
		x += c;
		y += c;
		z += c;
		return *this;
	}

	vec3& vec3::subtract(const float c)
	{
		x -= c;
		y -= c;
		z -= c;
		return *this;
	}

	vec3& vec3::multiply(const float c)
	{
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	vec3& vec3::divide(const float c)
	{
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	bool vec3::compare(const vec3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	vec3 operator+(const vec3& first, const vec3 &second)
	{
		return vec3(first.x, first.y,first.z).add(second);
	}

	vec3 operator-(const vec3& first, const vec3 &second)
	{
		return vec3(first.x, first.y, first.z).subtract(second);
	}

	vec3 operator*(const vec3& first, const vec3 &second)
	{
		return vec3(first.x, first.y, first.z).multiply(second);
	}

	vec3 operator/(const vec3& first, const vec3 &second)
	{
		return vec3(first.x, first.y, first.z).divide(second);
	}
	vec3 operator+(const vec3& first, const float c)
	{
		return vec3(first.x, first.y,first.z).add(c);
	}

	vec3 operator-(const vec3& first, const float c)
	{
		return vec3(first.x, first.y,first.z).subtract(c);
	}

	vec3 operator*(const vec3&  first, const float c)
	{
		return vec3(first.x, first.y,first.z).multiply(c);
	}

	vec3 operator/(const vec3& first, const float c)
	{
		return vec3(first.x, first.y, first.z).divide(c);
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

	vec3& vec3::operator+=(const float other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}

	vec3& vec3::operator-=(const float other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	vec3& vec3::operator*=(const float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	vec3& vec3::operator/=(const float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	bool vec3::operator==(const vec3 &other)
	{
		return compare(other);
	}

	bool vec3::operator!=(const vec3 &other)
	{
		return !compare(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vec)
	{
		return stream << vec.x << ", " << vec.y << ", " << vec.z;
	}
}