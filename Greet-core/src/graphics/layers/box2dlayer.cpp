#include "box2dlayer.h"

namespace greet { namespace graphics 
{
	Box2DLayer::Box2DLayer(Shader* shader, math::mat3 projectionMatrix, b2World* world)
			:Layer(new BatchRenderer(),shader,projectionMatrix), m_world(world)
	{
		for (b2Body* b = m_world->GetBodyList();b;b = b->GetNext())
		{
			math::vec2* vertices = math::getVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = math::getVertexCount(b);
				add(new RenderablePoly(math::vec2(b->GetPosition()),vertices,vertexCount, 0xffffffff));
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
			math::vec2* vertices = math::getVertices(b);
			if (vertices != NULL)
			{
				((RenderablePoly*)m_renderables[i])->setVertices(vertices,math::getVertexCount(b));
				((RenderablePoly*)m_renderables[i])->m_position = math::vec2(b->GetPosition());
			}
		}
		for (;b; b = b->GetNext())
		{
			math::vec2* vertices = math::getVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = math::getVertexCount(b);
				add(new RenderablePoly(math::vec2(b->GetPosition()),vertices, vertexCount, 0xffffffff));
			}
		}
	}
	
	void Box2DLayer::render() const
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Layer::render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}}
