#include "mat4.h"

#define _0_0 0 
#define _0_1 1 
#define _0_2 2 
#define _0_3 3 
#define _1_0 4 
#define _1_1 5 
#define _1_2 6 
#define _1_3 7 
#define _2_0 8 
#define _2_1 9 
#define _2_2 10
#define _2_3 11 
#define _3_0 12 
#define _3_1 13 
#define _3_2 14 
#define _3_3 15
#define SIZE 4
#define FLOATS SIZE*SIZE

namespace greet {
	namespace math {
		mat4::mat4()
		{
			memset(elements, 0.0f, FLOATS * sizeof(float));
		}

		mat4::mat4(float diagonal)
		{
			memset(elements, 0.0f, FLOATS * sizeof(float));
			elements[_0_0] = diagonal;
			elements[_1_1] = diagonal;
			elements[_2_2] = diagonal;
			elements[_3_3] = diagonal;
		}

		mat4::mat4(float* elem)
		{
			memcpy(elements,elem,FLOATS * sizeof(float));
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		mat4 mat4::orthographic(float left, float right, float top, float bottom, float near, float far)
		{
			mat4 result(1.0f);

			result.elements[_0_0] = 2.0f / (right - left);
			result.elements[_1_1] = 2.0f / (top - bottom);
			result.elements[_3_1] = -(right + left) / (right - left);
			result.elements[_3_2] = -(top + bottom) / (top - bottom);
			result.elements[_3_3] = -(far + near) / (far - near);

			return result;
		}

		mat4 mat4::projectionMatrix(float aspect, float fov, float near, float far)
		{
			mat4 result(1.0f);
			float tan2 = 1.0f/tan(toRadians(fov * 0.5f));
			result.elements[_0_0] = tan2 / aspect;
			result.elements[_1_1] = tan2;
			result.elements[_2_2] = (far + near) / (near - far);
			result.elements[_3_2] = 2 * (far * near) / (near - far);
			result.elements[_2_3] = -1;
			result.elements[_3_3] = 0;

			return result;
		}

		mat4 mat4::transformationMatrix(math::vec3 position, math::vec3 rotation, math::vec3 scale)
		{
			return 
				math::mat4::translate(position) *
				math::mat4::rotateX(rotation.x) *
				math::mat4::rotateY(rotation.y) *
				math::mat4::rotateZ(rotation.z) *
				math::mat4::scale(scale);
		}

		mat4 mat4::viewMatrix(math::vec3 position, math::vec3 rotation)
		{
			return
				math::mat4::rotateX(rotation.x) *
				math::mat4::rotateY(rotation.y) *
				math::mat4::rotateZ(rotation.z) *
				math::mat4::translate(-position.x, -position.y, -position.z);
		}

		mat4 mat4::tpCamera(math::vec3 position, float distance, float height, float rotation)
		{
			return rotateRX(asin(height)) * mat4::rotateY(90) * mat4::translate(vec3(sqrt(1 - height*height) * distance, - height * distance, 0)) * mat4::rotateY(rotation) * mat4::translate(-position.x,-position.y,-position.z);
		}


		mat4 mat4::translate(const vec3& translation)
		{
			mat4 result(1.0f);

			result.elements[_3_0] = translation.x;
			result.elements[_3_1] = translation.y;
			result.elements[_3_2] = translation.z;

			return result;
		}

		mat4 mat4::translate(const float& x, const float& y, const float& z)
		{
			mat4 result(1.0f);

			result.elements[_3_0] = x;
			result.elements[_3_1] = y;
			result.elements[_3_2] = z;
			return result;
		}

		mat4 mat4::scale(const vec3& scaling)
		{
			mat4 result(1.0f);

			result.elements[_0_0] = scaling.x;
			result.elements[_1_1] = scaling.y;
			result.elements[_2_2] = scaling.z;

			return result;
		}

		mat4 mat4::scale(const float& x, const float& y, const float& z)
		{
			mat4 result(1.0f);

			result.elements[_0_0] = x;
			result.elements[_1_1] = y;
			result.elements[_2_2] = z;

			return result;
		}

		mat4 mat4::rotateX(float deg)
		{
			return rotateRX(toRadians(deg));
		}

		mat4 mat4::rotateY(float deg)
		{
			return rotateRY(toRadians(deg));
		}

		mat4 mat4::rotateZ(float deg)
		{
			return rotateRZ(toRadians(deg));
		}
		mat4 mat4::rotateRX(float rad)
		{
			mat4 result(1.0f);
			float c = cos(rad);
			float s = sin(rad);
			result.elements[_1_1] = c;
			result.elements[_2_1] = -s;
			result.elements[_1_2] = s;
			result.elements[_2_2] = c;
			return result;
		}

		mat4 mat4::rotateRY(float rad)
		{
			mat4 result(1.0f);
			float c = cos(rad);
			float s = sin(rad);
			result.elements[_0_0] = c;
			result.elements[_0_2] = -s;
			result.elements[_2_0] = s;
			result.elements[_2_2] = c;
			return result;
		}
		mat4 mat4::rotateRZ(float rad)
		{
			mat4 result(1.0f);
			float c = cos(rad);
			float s = sin(rad);
			result.elements[_0_0] = c;
			result.elements[_1_0] = -s;
			result.elements[_0_1] = s;
			result.elements[_1_1] = c;
			return result;
		}

		mat4 mat4::rotate(float deg, const vec3& axis)
		{
			return rotateR(toRadians(deg),axis);
		}

		mat4 mat4::rotateR(float rad, const vec3& axis)
		{
			mat4 result(1.0f);

			float c = cos(rad);
			float s = sin(rad);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[_0_0] = x * omc + c;
			result.elements[_0_1] = y * x * omc + z * s;
			result.elements[_0_2] = x * z * omc - y * s;

			result.elements[_1_0] = x * y * omc - z * s;
			result.elements[_1_1] = y * omc + c;
			result.elements[_1_2] = y * z * omc + x * s;

			result.elements[_2_0] = x * z * omc + y * s;
			result.elements[_2_1] = y * z * omc - x * s;
			result.elements[_2_2] = z * omc + c;

			return result;
		}

		mat4 mat4::inverse(const mat4& inv)
		{
			float temp[FLOATS], det;
			int i;

			temp[0] = inv.elements[5] * inv.elements[10] * inv.elements[15] -
				inv.elements[5] * inv.elements[11] * inv.elements[14] -
				inv.elements[9] * inv.elements[6] * inv.elements[15] +
				inv.elements[9] * inv.elements[7] * inv.elements[14] +
				inv.elements[13] * inv.elements[6] * inv.elements[11] -
				inv.elements[13] * inv.elements[7] * inv.elements[10];

			temp[4] = -inv.elements[4] * inv.elements[10] * inv.elements[15] +
				inv.elements[4] * inv.elements[11] * inv.elements[14] +
				inv.elements[8] * inv.elements[6] * inv.elements[15] -
				inv.elements[8] * inv.elements[7] * inv.elements[14] -
				inv.elements[12] * inv.elements[6] * inv.elements[11] +
				inv.elements[12] * inv.elements[7] * inv.elements[10];

			temp[8] = inv.elements[4] * inv.elements[9] * inv.elements[15] -
				inv.elements[4] * inv.elements[11] * inv.elements[13] -
				inv.elements[8] * inv.elements[5] * inv.elements[15] +
				inv.elements[8] * inv.elements[7] * inv.elements[13] +
				inv.elements[12] * inv.elements[5] * inv.elements[11] -
				inv.elements[12] * inv.elements[7] * inv.elements[9];

			temp[12] = -inv.elements[4] * inv.elements[9] * inv.elements[14] +
				inv.elements[4] * inv.elements[10] * inv.elements[13] +
				inv.elements[8] * inv.elements[5] * inv.elements[14] -
				inv.elements[8] * inv.elements[6] * inv.elements[13] -
				inv.elements[12] * inv.elements[5] * inv.elements[10] +
				inv.elements[12] * inv.elements[6] * inv.elements[9];

			temp[1] = -inv.elements[1] * inv.elements[10] * inv.elements[15] +
				inv.elements[1] * inv.elements[11] * inv.elements[14] +
				inv.elements[9] * inv.elements[2] * inv.elements[15] -
				inv.elements[9] * inv.elements[3] * inv.elements[14] -
				inv.elements[13] * inv.elements[2] * inv.elements[11] +
				inv.elements[13] * inv.elements[3] * inv.elements[10];

			temp[5] = inv.elements[0] * inv.elements[10] * inv.elements[15] -
				inv.elements[0] * inv.elements[11] * inv.elements[14] -
				inv.elements[8] * inv.elements[2] * inv.elements[15] +
				inv.elements[8] * inv.elements[3] * inv.elements[14] +
				inv.elements[12] * inv.elements[2] * inv.elements[11] -
				inv.elements[12] * inv.elements[3] * inv.elements[10];

			temp[9] = -inv.elements[0] * inv.elements[9] * inv.elements[15] +
				inv.elements[0] * inv.elements[11] * inv.elements[13] +
				inv.elements[8] * inv.elements[1] * inv.elements[15] -
				inv.elements[8] * inv.elements[3] * inv.elements[13] -
				inv.elements[12] * inv.elements[1] * inv.elements[11] +
				inv.elements[12] * inv.elements[3] * inv.elements[9];

			temp[13] = inv.elements[0] * inv.elements[9] * inv.elements[14] -
				inv.elements[0] * inv.elements[10] * inv.elements[13] -
				inv.elements[8] * inv.elements[1] * inv.elements[14] +
				inv.elements[8] * inv.elements[2] * inv.elements[13] +
				inv.elements[12] * inv.elements[1] * inv.elements[10] -
				inv.elements[12] * inv.elements[2] * inv.elements[9];

			temp[2] = inv.elements[1] * inv.elements[6] * inv.elements[15] -
				inv.elements[1] * inv.elements[7] * inv.elements[14] -
				inv.elements[5] * inv.elements[2] * inv.elements[15] +
				inv.elements[5] * inv.elements[3] * inv.elements[14] +
				inv.elements[13] * inv.elements[2] * inv.elements[7] -
				inv.elements[13] * inv.elements[3] * inv.elements[6];

			temp[6] = -inv.elements[0] * inv.elements[6] * inv.elements[15] +
				inv.elements[0] * inv.elements[7] * inv.elements[14] +
				inv.elements[4] * inv.elements[2] * inv.elements[15] -
				inv.elements[4] * inv.elements[3] * inv.elements[14] -
				inv.elements[12] * inv.elements[2] * inv.elements[7] +
				inv.elements[12] * inv.elements[3] * inv.elements[6];

			temp[10] = inv.elements[0] * inv.elements[5] * inv.elements[15] -
				inv.elements[0] * inv.elements[7] * inv.elements[13] -
				inv.elements[4] * inv.elements[1] * inv.elements[15] +
				inv.elements[4] * inv.elements[3] * inv.elements[13] +
				inv.elements[12] * inv.elements[1] * inv.elements[7] -
				inv.elements[12] * inv.elements[3] * inv.elements[5];

			temp[14] = -inv.elements[0] * inv.elements[5] * inv.elements[14] +
				inv.elements[0] * inv.elements[6] * inv.elements[13] +
				inv.elements[4] * inv.elements[1] * inv.elements[14] -
				inv.elements[4] * inv.elements[2] * inv.elements[13] -
				inv.elements[12] * inv.elements[1] * inv.elements[6] +
				inv.elements[12] * inv.elements[2] * inv.elements[5];

			temp[3] = -inv.elements[1] * inv.elements[6] * inv.elements[11] +
				inv.elements[1] * inv.elements[7] * inv.elements[10] +
				inv.elements[5] * inv.elements[2] * inv.elements[11] -
				inv.elements[5] * inv.elements[3] * inv.elements[10] -
				inv.elements[9] * inv.elements[2] * inv.elements[7] +
				inv.elements[9] * inv.elements[3] * inv.elements[6];

			temp[7] = inv.elements[0] * inv.elements[6] * inv.elements[11] -
				inv.elements[0] * inv.elements[7] * inv.elements[10] -
				inv.elements[4] * inv.elements[2] * inv.elements[11] +
				inv.elements[4] * inv.elements[3] * inv.elements[10] +
				inv.elements[8] * inv.elements[2] * inv.elements[7] -
				inv.elements[8] * inv.elements[3] * inv.elements[6];

			temp[11] = -inv.elements[0] * inv.elements[5] * inv.elements[11] +
				inv.elements[0] * inv.elements[7] * inv.elements[9] +
				inv.elements[4] * inv.elements[1] * inv.elements[11] -
				inv.elements[4] * inv.elements[3] * inv.elements[9] -
				inv.elements[8] * inv.elements[1] * inv.elements[7] +
				inv.elements[8] * inv.elements[3] * inv.elements[5];

			temp[15] = inv.elements[0] * inv.elements[5] * inv.elements[10] -
				inv.elements[0] * inv.elements[6] * inv.elements[9] -
				inv.elements[4] * inv.elements[1] * inv.elements[10] +
				inv.elements[4] * inv.elements[2] * inv.elements[9] +
				inv.elements[8] * inv.elements[1] * inv.elements[6] -
				inv.elements[8] * inv.elements[2] * inv.elements[5];

			det = inv.elements[0] * temp[0] + inv.elements[1] * temp[4] + inv.elements[2] * temp[8] + inv.elements[3] * temp[12];

			if (det == 0)
				return inv;

			det = 1.0 / det;

			mat4 result(temp);

			return result;
		}

		mat4 mat4::cpy()
		{
			return mat4(elements);
		}

		mat4& mat4::multiply(const mat4 &other)
		{
			float data[FLOATS];
			for (int row = 0; row < SIZE; row++)
			{
				for (int col = 0; col < SIZE; col++)
				{
					float sum = 0.0f;
					for (int e = 0; e < SIZE; e++)
					{
						sum += elements[col + e * SIZE] * other.elements[e + row * SIZE];
					}
					data[col + row * SIZE] = sum;
				}
			}
			memcpy(elements, data, FLOATS * sizeof(float));

			return *this;
		}

		vec2 mat4::multiply(const vec2 &other) const
		{
			float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x + columns[3].x;
			float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y + columns[3].y;
			return vec2(x, y);
		}

		vec3 mat4::multiply(const vec3 &other) const
		{
			float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x;
			float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y;
			float z = columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z;
			return vec3(x, y, z);
		}

		vec4 mat4::multiply(const vec4 &other) const
		{
			float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w;
			float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w;
			float z = columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w;
			float w = columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w;
			return vec4(x, y, z, w);
		}

		mat4 operator*(mat4 first, const mat4 &second)
		{
			return first.multiply(second);
		}

		mat4& mat4::operator*=(const mat4 &other) {
			return multiply(other);
		}

		vec2 operator*(const mat4 &first, const vec2 &second)
		{
			return first.multiply(second);
		}

		vec3 operator*(const mat4 &first, const vec3 &second)
		{
			return first.multiply(second);
		}

		vec4 operator*(const mat4 &first, const vec4 &second)
		{
			return first.multiply(second);
		}
	}
}