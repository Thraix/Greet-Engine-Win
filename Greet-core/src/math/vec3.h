#pragma once

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif

#include <math.h>

namespace greet{
	namespace math{
	
	struct vec3// : public logging::Loggable
	{
		float x, y, z;
		vec3() = default;
		vec3(float x, float y, float z);

		float length() const;
		float dot(const vec3& vec) const;
		vec3 cross(const vec3& vec) const;
		vec3& normalize();
		vec3& rotate(const float& angle, const vec3& axis);
		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		vec3& add(const float other);
		vec3& subtract(const float other);
		vec3& multiply(const float other);
		vec3& divide(const float other);

		bool compare(const vec3& other);

		friend vec3 operator+(const vec3& first, const vec3 &second);
		friend vec3 operator-(const vec3& first, const vec3 &second);
		friend vec3 operator*(const vec3& first, const vec3 &second);
		friend vec3 operator/(const vec3& first, const vec3 &second);

		friend vec3 operator+(const vec3& first, const float c);
		friend vec3 operator-(const vec3& first, const float c);
		friend vec3 operator*(const vec3& first, const float c);
		friend vec3 operator/(const vec3& first, const float c);

		vec3& operator+=(const vec3 &other);
		vec3& operator-=(const vec3 &other);
		vec3& operator*=(const vec3 &other);
		vec3& operator/=(const vec3 &other);


		vec3& operator+=(const float c);
		vec3& operator-=(const float c);
		vec3& operator*=(const float c);
		vec3& operator/=(const float c);

		bool operator!=(const vec3 &second);
		bool operator==(const vec3 &second);
		
		//virtual std::string toString() const { return "vec3("+utils::toString(x)+","+utils::toString(y)+","+utils::toString(z)+")";}
	};

}}
