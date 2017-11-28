#pragma once

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif

#include <iostream>
#include <Box2D/Common/b2Math.h>
#include <math.h>
#include <logging/Log.h>

namespace Greet{
	
	struct Vec2
	{
	public:
		float x, y;
		Vec2();
		Vec2(float x, float y);
		Vec2(const b2Vec2& vec);

		float Length();
		float LengthSQ();
		float Dot(const Vec2& vec) const;
		float Cross(const Vec2& vec) const;
		Vec2& Abs();
		Vec2& Projected(const Vec2& vec);
		Vec2& Normalize();
		Vec2& Rotate(const float deg);
		Vec2& RotateR(const float rad);

		Vec2& Add(const Vec2& other);
		Vec2& Subtract(const Vec2& other);
		Vec2& Multiply(const Vec2& other);
		Vec2& Divide(const Vec2& other);

		Vec2& Add(const float other);
		Vec2& Subtract(const float other);
		Vec2& Multiply(const float other);
		Vec2& Divide(const float other);

		bool Compare(const Vec2& other);

		friend Vec2 operator+(const Vec2& first, const Vec2 &second);
		friend Vec2 operator-(const Vec2& first, const Vec2 &second);
		friend Vec2 operator*(const Vec2& first, const Vec2 &second);
		friend Vec2 operator/(const Vec2& first, const Vec2 &second);

		friend Vec2 operator+(const Vec2& first, const float c);
		friend Vec2 operator-(const Vec2& first, const float c);
		friend Vec2 operator*(const Vec2& first, const float c);
		friend Vec2 operator/(const Vec2& first, const float c);
		
		Vec2& operator+=(const Vec2 &other);
		Vec2& operator-=(const Vec2 &other);
		Vec2& operator*=(const Vec2 &other);
		Vec2& operator/=(const Vec2 &other);

		Vec2& operator+=(const float c);
		Vec2& operator-=(const float c);
		Vec2& operator*=(const float c);
		Vec2& operator/=(const float c);


		bool operator!=(const Vec2 &other);
		bool operator==(const Vec2 &other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& vec);

		inline float toRadians(float degrees)
		{
			return degrees * ((float)M_PI / 180.0f);
		}
	};

}
