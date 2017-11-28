#pragma once

#include "Renderable.h"


namespace Greet {
	class RenderablePoly : public Renderable
	{
	public:
		vec2 m_position;
		uint m_color;
	private:
		vec2* m_vertices;
		uint m_vertexCount;
		
	public:

		RenderablePoly(vec2 position, vec2* vertices, uint vertexCount, uint color)
			: m_position(position),m_vertices(vertices), m_vertexCount(vertexCount), m_color(color)
		{

		}

		~RenderablePoly()
		{
			delete[] m_vertices;
		}

		void setVertices(vec2* vertices, uint vertexCount)
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

		void setPosition(const vec2& position) override { m_position = position; }
		inline const vec2& getPosition() const { return m_position; }
		void setColor(uint color) override { m_color = color; }
		inline uint getColor() const override { return m_color; }
		void setSize(const vec2& size) override { }
		inline const vec2& getSize() const override { return vec2(1,1);}

		inline const vec2* getVertices() const { return m_vertices; }
		inline const uint getVertexCount() const { return m_vertexCount; }
	};
}
