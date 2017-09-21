#include "quaternion.h"

#include "math_func.h"


namespace Greet {

	quaternion::quaternion(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}

	float quaternion::length()
	{
		return (float)sqrt(x*x + y*y + z*z + w*w);
	}

	quaternion& quaternion::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
		return *this;
	}

	quaternion& quaternion::conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	quaternion& quaternion::multiply(const quaternion& other)
	{
		float w_ = w  * other.w - x  * other.x - y  * other.y - z  * other.z;
		float x_ = x  * other.w + w  * other.x + y  * other.z - z  * other.y;
		float y_ = y  * other.w + w  * other.y + z  * other.x - x  * other.z;
		float z_ = z  * other.w + w  * other.z + x  * other.y - y  * other.x;
		x = x_;
		y = y_;
		z = z_;
		w = w_;
		return *this;
	}

	quaternion& quaternion::multiply(const vec3& other)
	{
		float w_ = -x * other.x - y * other.y - z * other.z;
		float x_ =  w * other.x + y * other.z - z * other.y;
		float y_ =  w * other.y + z * other.x - x * other.z;
		float z_ =  w * other.z + x * other.y - y * other.x;
		x = x_;
		y = y_;
		z = z_;
		w = w_;
		return *this;
	}

	quaternion operator*(const quaternion& first, const quaternion &second)
	{
		return quaternion(first.x,first.y,first.z,first.w).multiply(second);
	}

	quaternion operator*(const quaternion& first, const vec3 &second)
	{
		return quaternion(first.x, first.y, first.z, first.w).multiply(second);
	}

	quaternion& quaternion::operator*=(const quaternion &other)
	{
		return multiply(other);
	}

	quaternion& quaternion::operator*=(const vec3 &other)
	{
		return multiply(other);
	}

}