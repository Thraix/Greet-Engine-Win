#include "mat3.h"
namespace greet{ namespace math{
	mat3::mat3()
	{
		for (int i = 0; i < 9; i++)
			elements[i] = 0.0f;
	}

	mat3::mat3(float diagonal)
	{
		for (int i = 0; i < 9; i++)
			elements[i] = 0.0f;
		elements[0] = diagonal;
		elements[4] = diagonal;
		elements[8] = diagonal;
	}

	mat3::mat3(float* elem)
	{
		for (int i = 0;i < 9;i++)
			elements[i] = elem[i];
	}

	mat3 mat3::identity()
	{
		return mat3(1.0f);
	}

	mat3 mat3::orthographic(float left, float right, float top, float bottom)
	{
		mat3 result(1.0f);

		result.elements[0] = 2.0f / (right - left);
		result.elements[4] = 2.0f / (top - bottom);
		result.elements[6] = -(right + left) / (right - left);
		result.elements[7] = -(top + bottom) / (top - bottom);

		return result;
	}

	mat3 mat3::quad(float x, float y, float width, float height)
	{
		mat3 result(1.0f);

		result.elements[6] = x;
		result.elements[7] = y;
		result.elements[0] = width;
		result.elements[4] = height;

		return result;
	}

	mat3 mat3::quad(const vec2& pos, const vec2& size)
	{
		mat3 result(1.0f);

		result.elements[6] = pos.x;
		result.elements[7] = pos.y;
		result.elements[0] = size.x;
		result.elements[4] = size.y;

		return result;
	}

	mat3 mat3::translate(const vec2& translation)
	{
		mat3 result(1.0f);

		result.elements[6] = translation.x;
		result.elements[7] = translation.y;

		return result;
	}

	mat3 mat3::translate(const float& x, const float& y)
	{
		mat3 result(1.0f);

		result.elements[6] = x;
		result.elements[7] = y;

		return result;
	}

	mat3 mat3::scale(const vec2& scaling)
	{
		mat3 result(1.0f);

		result.elements[0] = scaling.x;
		result.elements[4] = scaling.y;

		return result;
	}

	mat3 mat3::scale(const float& x, const float& y)
	{
		mat3 result(1.0f);

		result.elements[0] = x;
		result.elements[4] = y;

		return result;
	}

	mat3 mat3::rotate(float deg)
	{
		mat3 result(1.0f);
		float r = toRadians(deg);
		float s = sin(r);
		float c = cos(r);

		result.elements[0] = c;
		result.elements[1] = s;
		result.elements[3] = -s;
		result.elements[4] = c;

		return result;
	}

	mat3 mat3::rotateR(float rad)
	{
		mat3 result(1.0f);
		float s = sin(rad);
		float c = cos(rad);

		result.elements[0] = c;
		result.elements[1] = s;
		result.elements[3] = -s;
		result.elements[4] = c;

		return result;
	}

	mat3 mat3::shear(const vec2& shearing)
	{
		mat3 result(1.0f);

		result.elements[3] = shearing.x;
		result.elements[1] = shearing.y;

		return result;
	}

	mat3 mat3::shear(const float& x, const float& y)
	{
		mat3 result(1.0f);

		result.elements[3] = x;
		result.elements[1] = y;

		return result;
	}

	mat3& mat3::inverse()
	{
		float temp[9],det;

		temp[0] = elements[4] * elements[8] - elements[7] * elements[5];
		temp[1] = elements[7] * elements[2] - elements[1] * elements[8];
		temp[2] = elements[1] * elements[5] - elements[4] * elements[2];

		temp[3] = elements[6] * elements[5] - elements[3] * elements[8];
		temp[4] = elements[0] * elements[8] - elements[6] * elements[2];
		temp[5] = elements[3] * elements[2] - elements[0] * elements[5];

		temp[6] = elements[3] * elements[7] - elements[6] * elements[4];
		temp[7] = elements[6] * elements[1] - elements[0] * elements[7];
		temp[8] = elements[0] * elements[4] - elements[3] * elements[1];

		det = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[7];
		
		if (det == 0)
			return *this;

		det = 1.0f / det;

		for (int i = 0; i < 9; i++)
			elements[i] = temp[i] * det;
		
		return *this;
	}

	mat3 mat3::cpy()
	{
		return mat3(elements);
	}

	mat3& mat3::multiply(const mat3 &other)
	{
		float data[9];
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 3; e++)
				{
					sum += elements[col + e * 3] * other.elements[e + row * 3];
				}
				data[col + row * 3] = sum;
			}
		}
		memcpy(elements, data, 9*sizeof(float));

		return *this;
	}

	vec2 mat3::multiply(const vec2 &other) const
	{
		float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x;
		float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y;
		return vec2(x, y);
	}

	vec3 mat3::multiply(const vec3 &other) const
	{
		float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z;
		float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z;
		float z = columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z;
		return vec3(x,y,z);
	}

	mat3 operator*(mat3 first, const mat3 &second)
	{
		return first.multiply(second);
	}

	mat3& mat3::operator*=(const mat3 &other){
		return multiply(other);
	}

	vec2 operator*(const mat3 &first, const vec2 &second)
	{
		return first.multiply(second);
	}

	vec3 operator*(const mat3 &first, const vec3 &second)
	{
		return first.multiply(second);
	}
}}