#include "box2dLayer.h"

namespace Greet {

	Box2DLayer::Box2DLayer(const Shader& shader, Mat3 projectionMatrix, b2World* world)
		:Layer(new BatchRenderer(),shader,projectionMatrix), m_world(world)
	{
		for (b2Body* b = m_world->GetBodyList();b;b = b->GetNext())
		{
			Vec2* vertices = Math::GetVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = Math::GetVertexCount(b);
				Add(new RenderablePoly(Vec2(b->GetPosition()),vertices,vertexCount, 0xffffffff));
			}
		}
	}
	
	void Box2DLayer::Update(float timeElapsed)
	{
		uint length = m_world->GetBodyCount();
		uint renderables = Size();
		uint i = 0;
		b2Body* b = m_world->GetBodyList();
		for (;b && i < renderables;i++,b = b->GetNext())
		{
			Vec2* vertices = Math::GetVertices(b);
			if (vertices != NULL)
			{
				((RenderablePoly*)m_renderables[i])->SetVertices(vertices, Math::GetVertexCount(b));
				((RenderablePoly*)m_renderables[i])->m_position = Vec2(b->GetPosition());
			}
		}
		for (;b; b = b->GetNext())
		{
			Vec2* vertices = Math::GetVertices(b);
			if (vertices != NULL)
			{
				uint vertexCount = Math::GetVertexCount(b);
				Add(new RenderablePoly(Vec2(b->GetPosition()),vertices, vertexCount, 0xffffffff));
			}
		}
	}
	
	void Box2DLayer::Render() const
	{
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		Layer::Render();
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}
