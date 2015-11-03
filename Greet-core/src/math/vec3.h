#pragma once
#include <iostream>

namespace greet{
	namespace math{
	
	struct vec3
	{
		float x, y, z;
		vec3() = default;
		vec3(float x, float y, float z);

		float length();

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);
		bool compare(const vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec3 &vec);

		friend vec3& operator+(vec3& first, const vec3 &second);
		friend vec3& operator-(vec3& first, const vec3 &second);
		friend vec3& operator*(vec3& first, const vec3 &second);
		friend vec3& operator/(vec3& first, const vec3 &second);

		vec3& operator+=(const vec3 &other);
		vec3& operator-=(const vec3 &other);
		vec3& operator*=(const vec3 &other);
		vec3& operator/=(const vec3 &other);

		bool operator!=(const vec3 &second);
		bool operator==(const vec3 &second);
	};

}}