#pragma once

#include <vector>
#include <internal/greetgl.h>
#include <math/maths.h>
#include <logging/logger.h>

namespace greet{ namespace graphics{

	class Renderer
	{
	protected:
		std::vector<math::mat3> m_transformationStack;
		const math::mat3* m_transformationBack;

		Renderer()
		{
			m_transformationStack.push_back(math::mat3::identity());
			m_transformationBack = &m_transformationStack.back();
		}

	public:
		void pushMatrix(const math::mat3 &matrix, bool override = false)
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
				LOG_WARNING("RENDERER", "Trying to pop the last matrix.");
			m_transformationBack = &m_transformationStack.back();
		}

		const math::mat3& getMatrix()
		{
			return *m_transformationBack;
		}

		const math::mat3& getMatrix(uint index)
		{
			if (index >= 0 && index<m_transformationStack.size())
				return m_transformationStack[index];
			LOG_WARNING("RENDERER", "Index out of bound: ", "index:", index, ",size:", m_transformationStack.size());
			return m_transformationStack[0];
		}
	};
}}