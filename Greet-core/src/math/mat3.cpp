#include "Mat3.h"
namespace Greet{
	Mat3::Mat3()
	{
		for (int i = 0; i < 9; i++)
			elements[i] = 0.0f;
	}

	Mat3::Mat3(float diagonal)
	{
		for (int i = 0; i < 9; i++)
			elements[i] = 0.0f;
		elements[0] = diagonal;
		elements[4] = diagonal;
		elements[8] = diagonal;
	}

	Mat3::Mat3(float* elem)
	{
		for (int i = 0;i < 9;i++)
			elements[i] = elem[i];
	}

	Mat3 Mat3::Identity()
	{
		return Mat3(1.0f);
	}

	Mat3 Mat3::Orthographic(float left, float right, float top, float bottom)
	{
		Mat3 result(1.0f);

		result.elements[0] = 2.0f / (right - left);
		result.elements[4] = 2.0f / (top - bottom);
		result.elements[6] = -(right + left) / (right - left);
		result.elements[7] = -(top + bottom) / (top - bottom);

		return result;
	}

	Mat3 Mat3::Quad(float x, float y, float width, float height)
	{
		Mat3 result(1.0f);

		result.elements[6] = x;
		result.elements[7] = y;
		result.elements[0] = width;
		result.elements[4] = height;

		return result;
	}

	Mat3 Mat3::Quad(const Vec2& pos, const Vec2& size)
	{
		Mat3 result(1.0f);

		result.elements[6] = pos.x;
		result.elements[7] = pos.y;
		result.elements[0] = size.x;
		result.elements[4] = size.y;

		return result;
	}

	Mat3 Mat3::Translate(const Vec2& translation)
	{
		Mat3 result(1.0f);

		result.elements[6] = translation.x;
		result.elements[7] = translation.y;

		return result;
	}

	Mat3 Mat3::Translate(const float& x, const float& y)
	{
		Mat3 result(1.0f);

		result.elements[6] = x;
		result.elements[7] = y;

		return result;
	}

	Mat3 Mat3::Scale(const Vec2& scaling)
	{
		Mat3 result(1.0f);

		result.elements[0] = scaling.x;
		result.elements[4] = scaling.y;

		return result;
	}

	Mat3 Mat3::Scale(const float& x, const float& y)
	{
		Mat3 result(1.0f);

		result.elements[0] = x;
		result.elements[4] = y;

		return result;
	}

	Mat3 Mat3::Rotate(float deg)
	{
		Mat3 result(1.0f);
		float r = Math::ToRadians(deg);
		float s = sin(r);
		float c = cos(r);

		result.elements[0] = c;
		result.elements[1] = s;
		result.elements[3] = -s;
		result.elements[4] = c;

		return result;
	}

	Mat3 Mat3::RotateR(float rad)
	{
		Mat3 result(1.0f);
		float s = sin(rad);
		float c = cos(rad);

		result.elements[0] = c;
		result.elements[1] = s;
		result.elements[3] = -s;
		result.elements[4] = c;

		return result;
	}

	Mat3 Mat3::Shear(const Vec2& shearing)
	{
		Mat3 result(1.0f);

		result.elements[3] = shearing.x;
		result.elements[1] = shearing.y;

		return result;
	}

	Mat3 Mat3::Shear(const float& x, const float& y)
	{
		Mat3 result(1.0f);

		result.elements[3] = x;
		result.elements[1] = y;

		return result;
	}

	Mat3& Mat3::Inverse()
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

	Mat3 Mat3::Cpy()
	{
		return Mat3(elements);
	}

	Mat3& Mat3::Multiply(const Mat3 &other)
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

	Vec2 Mat3::Multiply(const Vec2 &other) const
	{
		float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x;
		float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y;
		return Vec2(x, y);
	}

	Vec3 Mat3::Multiply(const Vec3 &other) const
	{
		float x = columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z;
		float y = columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z;
		float z = columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z;
		return Vec3(x,y,z);
	}

	Mat3 operator*(Mat3 first, const Mat3 &second)
	{
		return first.Multiply(second);
	}

	Mat3& Mat3::operator*=(const Mat3 &other){
		return Multiply(other);
	}

	Vec2 operator*(const Mat3 &first, const Vec2 &second)
	{
		return first.Multiply(second);
	}

	Vec3 operator*(const Mat3 &first, const Vec3 &second)
	{
		return first.Multiply(second);
	}
}