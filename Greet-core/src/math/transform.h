#pragma once

#include "mat3.h"

namespace Greet {
	class Transform
	{
	public:
		mat3 m_matrix;
	private:

	public:
		Transform()
			: m_matrix(mat3(1))
		{

		}

		Transform(mat3 matrix)

		{
			m_matrix = matrix;
		}

		Transform& init(float diagonal = 1)
		{
			m_matrix = mat3(diagonal);
			return *this;
		}

		Transform& scale(float x, float y)
		{
			m_matrix *= mat3::scale(x, y);
			return *this;
		}

		Transform& scale(vec2 scale)
		{
			m_matrix *= mat3::scale(scale);
			return *this;
		}

		Transform& translate(float x, float y)
		{
			m_matrix *= mat3::translate(x,y);
			return *this;
		}

		Transform& translate(vec2 translate)
		{
			m_matrix *= mat3::translate(translate);
			return *this;
		}

		Transform& rotate(float deg)
		{
			m_matrix *= mat3::rotate(deg);
			return *this;
		}

		Transform& rotateR(float rad)
		{
			m_matrix *= mat3::rotateR(rad);
			return *this;
		}

		Transform& shear(float x, float y)
		{
			m_matrix *= mat3::shear(x, y);
			return *this;
		}

		Transform& shear(vec2 shear)
		{
			m_matrix *= mat3::shear(shear);
			return *this;
		}

		inline const mat3& getMatrix() const { return m_matrix; }
	};
}
