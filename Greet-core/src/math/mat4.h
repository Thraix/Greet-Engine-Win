#pragma once

#include "vec2.h"
#include "vec3.h"
#include "math_func.h"
#include <string.h>

namespace greet {
	namespace math {
		struct mat4
		{
			union
			{
				float elements[4 * 4];
				struct
				{
					vec4 columns[4];
				};
			};

			mat4();
			mat4(float diagonal);
			mat4(float* elem);

			vec4 getColumn(int index)
			{
				return columns[index];
			}

			static mat4 identity();
			static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
			static mat4 projectionMatrix(float aspect, float fov, float near, float far);

			static mat4 transformationMatrix(math::vec3 position, math::vec3 rotation, math::vec3 scale);
			static mat4 viewMatrix(math::vec3 position, math::vec3 rotation);

			/* 
			View Matrix of a third person camera around an object.
				position	- Position of the object
				distance	- distance from the object
				height		- height above the object, between -1 and 1
				rotation	- angle around the object
			*/
			static mat4 tpCamera(math::vec3 position, float distance, float height, float rotation);

			static mat4 translate(const vec3& translation);
			static mat4 scale(const vec3& scaling);

			static mat4 translate(const float& x, const float& y, const float& z);
			static mat4 scale(const float& x, const float& y, const float& z);

			static mat4 rotateX(float deg);
			static mat4 rotateY(float deg);
			static mat4 rotateZ(float deg);

			static mat4 rotateRX(float rad);
			static mat4 rotateRY(float rad);
			static mat4 rotateRZ(float rad);
			static mat4 rotate(float deg, const vec3& axis);
			static mat4 rotateR(float rad, const vec3& axis);

			static mat4 inverse(const mat4& inv);

			mat4 cpy();

			mat4& multiply(const mat4 &other);
			vec2 multiply(const vec2 &other) const;
			vec3 multiply(const vec3 &other) const;
			vec4 multiply(const vec4 &other) const;

			friend mat4 operator*(mat4 first, const mat4 &second);
			mat4& operator*=(const mat4 &other);

			friend vec2 operator*(const mat4& first, const vec2 &second);
			friend vec3 operator*(const mat4& first, const vec3 &second);
			friend vec4 operator*(const mat4& first, const vec4 &second);

		};
	}
}
