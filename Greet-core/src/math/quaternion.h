#pragma once

#include "vec3.h"

namespace greet { namespace math {

class quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	quaternion(float x, float y, float z, float w);

	float length();
	quaternion& normalize();
	quaternion& conjugate();

	quaternion& multiply(const quaternion& other);
	quaternion& multiply(const math::vec3& other);

	friend quaternion operator*(const quaternion& first, const quaternion &second);
	friend quaternion operator*(const quaternion& first, const vec3 &second);

	quaternion& operator*=(const quaternion &other);
	quaternion& operator*=(const vec3 &other);
};

}}