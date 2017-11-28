#pragma once

#include <vector>
#include <internal/GreetGL.h>
#include <math/Maths.h>
#include <logging/Log.h>

namespace Greet{

	class Renderer
	{
	protected:
		std::vector<Mat3> m_transformationStack;
		const Mat3* m_transformationBack;

		Renderer()
		{
			m_transformationStack.push_back(Mat3::Identity());
			m_transformationBack = &m_transformationStack.back();
		}

	public:
		void PushMatrix(const Mat3 &matrix, bool override = false)
		{
			if (override)
				m_transformationStack.push_back(matrix);
			else
				m_transformationStack.push_back(*m_transformationBack * matrix);
			m_transformationBack = &m_transformationStack.back();

		}
		void PopMatrix()
		{
			if (m_transformationStack.size() > 1)
				m_transformationStack.pop_back();
			else
				Log::Warning("Trying to pop the last matrix.");
			m_transformationBack = &m_transformationStack.back();
		}

		const Mat3& GetMatrix()
		{
			return *m_transformationBack;
		}

		const Mat3& GetMatrix(uint index)
		{
			if (index >= 0 && index<m_transformationStack.size())
				return m_transformationStack[index];
			Log::Warning("Index out of bound: ", "index: ", index, ",size: ", m_transformationStack.size());
			return m_transformationStack[0];
		}
	};
}