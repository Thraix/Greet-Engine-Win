#pragma once

#include <vector>
#include <greetgl.h>
#include <math/maths.h>
#include "font.h"

namespace greet{ namespace graphics{

	class Renderable;
	class Renderable2D;
	class Renderable4Poly;
	class RenderablePoly;
	class Label;

	class Renderer2D
	{
	protected:
		std::vector<math::mat3> m_transformationStack;
		const math::mat3* m_transformationBack;

	protected:
		Renderer2D()
		{ 
			m_transformationStack.push_back(math::mat3::identity());
			m_transformationBack = &m_transformationStack.back();
		}

	public:

		virtual void begin(){}
		virtual void submit(const Renderable2D *renderable) = 0;
		virtual void submit(const RenderablePoly *renderable) = 0;
		virtual void submit(const Renderable4Poly* renderable) = 0;
		virtual void submit(const math::Transform& transformation, uint texID, math::vec2 texPos, math::vec2 texSize, uint color) = 0;
		virtual void submitString(const Label* label, bool shadow = false) = 0;
		virtual void end(){}
		virtual void flush() = 0;

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
				GREET_WARN("RENDERER2D","Trying to pop the last matrix.");
			
			m_transformationBack = &m_transformationStack.back();
		}

		const math::mat3& getMatrix()
		{
			return *m_transformationBack;
		}

		const math::mat3& getMatrix(uint index)
		{
			if(index>=0&&index<m_transformationStack.size())
				return m_transformationStack[index];
			GREET_WARN("RENDERER2D", "Index out of bound: ", "index:", index, ",size:", m_transformationStack.size());
			return m_transformationStack[0];
		}
	};
}}