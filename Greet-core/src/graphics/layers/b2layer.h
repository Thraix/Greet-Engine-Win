#pragma once

#include <Box2D\Box2D.h>
#include <graphics\layers\layer.h>


namespace greet { namespace graphics {
	class Box2DLayer : public Layer
	{
	public:
		b2World* m_world;


	public:
		Box2DLayer(Renderer2D* renderer, Shader* shader, math::mat3 projectionMatrix, b2World* world)
			:Layer(renderer,shader,projectionMatrix), m_world(world)
		{
			uint length = m_world->GetBodyCount();
			b2Body* bodies = m_world->GetBodyList();
			for (uint i = 0;i < length;i++)
			{
				
			}
		}

		void update(float timeElapsed) override
		{
			
		}

		void render() const override
		{

			Layer::render();

		}
	};
}}
