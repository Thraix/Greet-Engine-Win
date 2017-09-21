#pragma once

#include <vector>
#include <internal/Greetgl.h>
#include <math/maths.h>
#include <logging/log.h>

namespace Greet{

	class Renderer
	{
	protected:
		std::vector<mat3> m_transformationStack;
		const mat3* m_transformationBack;

		Renderer()
		{
			m_transformationStack.push_back(mat3::identity());
			m_transformationBack = &m_transformationStack.back();
		}

	public:
		void pushMatrix(const mat3 &matrix, bool override = false)
		{
			if (override)
				m_transformationStack.push_back(matrix);
			else
				m_transformationStack.push_back(*m_transformationBack * matrix);
			m_transformationBack = &m_transformationStack.back();

		}
		void popMatrix()
		{
			if (m_transformationStack.size() > 1)
				m_transformationStack.pop_back();
			else
				Log::warning("Trying to pop the last matrix.");
			m_transformationBack = &m_transformationStack.back();
		}

		const mat3& getMatrix()
		{
			return *m_transformationBack;
		}

		const mat3& getMatrix(uint index)
		{
			if (index >= 0 && index<m_transformationStack.size())
				return m_transformationStack[index];
			Log::warning("Index out of bound: ", "index: ", index, ",size: ", m_transformationStack.size());
			return m_transformationStack[0];
		}
	};
}