#pragma once

#include <Box2D\Box2D.h>
#include <graphics\layers\layer.h>
#include <entity\entity.h>
#include <graphics\renderable2d.h>
#include <utils\log.h>

namespace greet { namespace graphics {
	class Box2DLayer : public Layer
	{
	public:
		b2World* m_world;


	public:
		Box2DLayer(Shader* shader, math::mat3 projectionMatrix, b2World* world)
			:Layer(new BatchRenderer(),shader,projectionMatrix), m_world(world)
		{
			for (b2Body* b = m_world->GetBodyList();b;b = b->GetNext())
			{
				math::vec2* vertices = math::getVertices(b);
				if (vertices != NULL)
				{
					uint vertexCount = math::getVertexCount(b);
					push(new RenderablePoly(math::vec2(b->GetPosition()),vertices,vertexCount, 0xffffffff));
				}
			}
		}

		void update(float timeElapsed) override
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
					push(new RenderablePoly(math::vec2(b->GetPosition()),vertices, vertexCount, 0xffffffff));
				}
			}
		}

		void render() const override
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			Layer::render();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	};
}}
