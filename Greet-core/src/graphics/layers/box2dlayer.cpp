#include "box2dlayer.h"

namespace Greet {

	Box2DLayer::Box2DLayer(Shader* shader, mat3 projectionMatrix, b2World* world)
			:Layer(new BatchRenderer(),shader,projectionMatrix), m_world(world)
	{
		for (b2Body* b = m_world->GetBodyList();b;b = b->GetNext())
		{
			vec2* vertices = Math::getVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = Math::getVertexCount(b);
				add(new RenderablePoly(vec2(b->GetPosition()),vertices,vertexCount, 0xffffffff));
			}
		}
	}
	
	void Box2DLayer::update(float timeElapsed)
	{
		uint length = m_world->GetBodyCount();
		uint renderables = size();
		uint i = 0;
		b2Body* b = m_world->GetBodyList();
		for (;b && i < renderables;i++,b = b->GetNext())
		{
			vec2* vertices = Math::getVertices(b);
			if (vertices != NULL)
			{
				((RenderablePoly*)m_renderables[i])->setVertices(vertices, Math::getVertexCount(b));
				((RenderablePoly*)m_renderables[i])->m_position = vec2(b->GetPosition());
			}
		}
		for (;b; b = b->GetNext())
		{
			vec2* vertices = Math::getVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = Math::getVertexCount(b);
				add(new RenderablePoly(vec2(b->GetPosition()),vertices, vertexCount, 0xffffffff));
			}
		}
	}
	
	void Box2DLayer::render() const
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Layer::render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
