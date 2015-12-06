#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <Box2D\Common\b2Math.h>
#include <math.h>

namespace greet{
	namespace math{
	
	struct vec2
	{
		float x, y;
		vec2();
		vec2(float x, float y);
		vec2(const b2Vec2& vec);

		float length();
		float lengthSQ();
		float dot(const math::vec2& vec) const;
		vec2& abs();
		vec2& projected(const math::vec2& vec);
		vec2& normalize();
		vec2& rotate(const float deg);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		vec2& add(const float other);
		vec2& subtract(const float other);
		vec2& multiply(const float other);
		vec2& divide(const float other);

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
		
		vec2& operator=(const b2Vec2& other);

		vec2& operator+=(const vec2 &other);
		vec2& operator-=(const vec2 &other);
		vec2& operator*=(const vec2 &other);
		vec2& operator/=(const vec2 &other);

		vec2& operator+=(const float c);
		vec2& operator-=(const float c);
		vec2& operator*=(const float c);
		vec2& operator/=(const float c);


		bool operator!=(const vec2 &other);
		bool operator==(const vec2 &other);

		inline float toRadians(float degrees)
		{
			return degrees * ((float)M_PI / 180.0f);
		}
	};

}}