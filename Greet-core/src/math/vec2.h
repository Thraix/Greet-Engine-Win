#pragma once

#include "math_func.h"
#include <iostream>

namespace greet{
	namespace math{
	
	struct vec2
	{
		float x, y;
		vec2();
		vec2(float x, float y);

		float length();
		float lengthSQ();
		vec2& normalize();
		vec2& rotate(const float deg);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		bool compare(const vec2& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec2 &vec);

		friend vec2 operator+(const vec2& first, const vec2 &second);
		friend vec2 operator-(const vec2& first, const vec2 &second);
		friend vec2 operator*(const vec2& first, const vec2 &second);
		friend vec2 operator/(const vec2& first, const vec2 &second);

		friend vec2 operator+(const vec2& first, const float c);
		friend vec2 operator-(const vec2& first, const float c);
		friend vec2 operator*(const vec2& first, const float c);
		friend vec2 operator/(const vec2& first, const float c);

		vec2& operator+=(const vec2 &other);
		vec2& operator-=(const vec2 &other);
		vec2& operator*=(const vec2 &other);
		vec2& operator/=(const vec2 &other);

		vec2& operator+=(const float other);
		vec2& operator-=(const float other);
		vec2& operator*=(const float other);
		vec2& operator/=(const float other);

		bool operator!=(const vec2 &other);
		bool operator==(const vec2 &other);
	};

}}