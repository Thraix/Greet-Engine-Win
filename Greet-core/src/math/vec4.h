#pragma once
#include <iostream>

namespace greet{
	namespace math{
	
	struct vec4
	{
			float x, y, z, w;
		vec4();
		vec4(float x, float y, float z, float w);

		float length();

		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& multiply(const vec4& other);
		vec4& divide(const vec4& other);
		bool compare(const vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec4 &vec);

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
	};

}}