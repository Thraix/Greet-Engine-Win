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

		inline const math::vec2& getPosition() const { return m_position; }
		inline const uint getColor() const { return m_color; }
		inline const math::vec2* getVertices() const { return m_vertices; }
		inline const uint getVertexCount() const { return m_vertexCount; }
	};
}}