#include "vec2.h"
#include "vec3.h"
#include "math_func.h"

namespace greet{ namespace math{
	struct mat3
	{
		union
		{
			float elements[3 * 3];
			vec3 columns[3];
		};

		mat3();
		mat3(float diagonal);
		mat3(float* elem);

		vec3 getColumn(int index)
		{
			return columns[index];
		}

		static mat3 identity();
		static mat3 orthographic(float left, float right, float top, float bottom);
		static mat3 quad(float x, float y, float width, float height);
		static mat3 quad(const vec2& pos, const vec2& size);

		static mat3 translate(const vec2& translation);
		static mat3 scale(const vec2& scaling);
		static mat3 shear(const vec2& shearing);

		static mat3 translate(const float& x, const float& y);
		static mat3 scale(const float& x, const float& y);
		static mat3 rotate(float deg);
		static mat3 shear(const float& x, const float& y);

		mat3& inverse();
		mat3 cpy();

		mat3& multiply(const mat3 &other);
		vec2 multiply(const vec2 &other) const;
		vec3 multiply(const vec3 &other) const;

		friend mat3 operator*(mat3 first, const mat3 &second);
		mat3& operator*=(const mat3 &other);

		friend vec2 operator*(const mat3& first, const vec2 &second);
		friend vec3 operator*(const mat3& first, const vec3 &second);

	};
}}