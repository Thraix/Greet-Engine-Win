#pragma once

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <iostream>

namespace Greet{
	
	struct vec4
	{
		float x, y, z, w;
		vec4();
		vec4(float x, float y, float z, float w);

		float Length();
		
		vec4& Add(const vec4& other);
		vec4& Subtract(const vec4& other);
		vec4& Multiply(const vec4& other);
		vec4& Divide(const vec4& other);
		bool Compare(const vec4& other);

		friend vec4& operator+(vec4& first, const vec4 &second);
		friend vec4& operator-(vec4& first, const vec4 &second);
		friend vec4& operator*(vec4& first, const vec4 &second);
		friend vec4& operator/(vec4& first, const vec4 &second);

		vec4& operator+=(const vec4 &other);
		vec4& operator-=(const vec4 &other);
		vec4& operator*=(const vec4 &other);
		vec4& operator/=(const vec4 &other);

		bool operator!=(const vec4 &second);
		bool operator==(const vec4 &second);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vec);
		
	};
}
