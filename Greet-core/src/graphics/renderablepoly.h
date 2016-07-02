#pragma once

#include "renderable.h"


namespace greet { namespace graphics {
	class RenderablePoly : public Renderable
	{
	public:
		math::vec2 m_position;
		uint m_color;
	private:
		math::vec2* m_vertices;
		uint m_vertexCount;
		
	public:

		RenderablePoly(math::vec2 position, math::vec2* vertices, uint vertexCount, uint color)
			: m_position(position),m_vertices(vertices), m_vertexCount(vertexCount), m_color(color)
		{

		}

		~RenderablePoly()
		{
			delete[] m_vertices;
		}

		void setVertices(math::vec2* vertices, uint vertexCount)
		{
			m_vertices = vertices;
			m_vertexCount = vertexCount;
		}

		virtual void submit(Renderer2D* renderer) const override
		{
			if (render)
				renderer->submit(this);
		}

		virtual bool update(float timeElapsed) override
		{
			return true;
		}

		void setPosition(const math::vec2& position) override { m_position = position; }
		inline const math::vec2& getPosition() const { return m_position; }
		void setColor(uint color) override { m_color = color; }
		inline uint getColor() const override { return m_color; }
		void setSize(const math::vec2& size) override { }
		inline const math::vec2& getSize() const override { return math::vec2(1,1);}

		inline const math::vec2* getVertices() const { return m_vertices; }
		inline const uint getVertexCount() const { return m_vertexCount; }
	};
}}
