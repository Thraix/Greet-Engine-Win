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
		Box2DLayer(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix, b2World* world)
			:Layer(renderer,shader,projectionMatrix), m_world(world)
		{
			for (b2Body* b = m_world->GetBodyList();b;b = b->GetNext())
			{
				math::vec4 rectangle = math::getRectangle(b);
				if (rectangle.z != 0 && rectangle.w != 0)
				{
					math::Transform t = math::Transform().translate(b->GetPosition()).rotateR(b->GetAngle()).translate(-rectangle.z/2.0f, -rectangle.w/2.0f).scale(rectangle.z,rectangle.w);
					push(new Renderable2D(t, 0xffffffff, NULL));
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
				math::vec4 rectangle = math::getRectangle(b);
				if (rectangle.z != 0 && rectangle.w != 0)
				{
					math::Transform t = math::Transform().translate(b->GetPosition()).rotateR(b->GetAngle()).translate(-rectangle.z / 2.0f, -rectangle.w / 2.0f).scale(rectangle.z, rectangle.w);
					((Renderable2D*)m_renderables[i])->m_transform = t;
				}
			}
			for (;b; b = b->GetNext())
			{
				math::vec4 rectangle = math::getRectangle(b);
				if (rectangle.z != 0 && rectangle.w != 0)
				{
					math::Transform t = math::Transform().translate(b->GetPosition()).rotateR(b->GetAngle()).translate(-rectangle.z / 2.0f, -rectangle.w / 2.0f).scale(rectangle.z, rectangle.w);
					push(new Renderable2D(t, 0xffffffff, NULL));
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
