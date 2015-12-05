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
			uint length = m_world->GetBodyCount();
			b2Body* bodies = m_world->GetBodyList();
			for (uint i = 0;i < length;i++)
			{
				b2Fixture f = bodies[i].GetFixtureList()[0];
				if (f.GetType() == b2Shape::e_polygon)
				{
					b2PolygonShape* shape = (b2PolygonShape*)f.GetShape();
					if (shape->GetVertexCount() == 4)
					{
						math::vec2 pos1 = shape->GetVertex(0);
						math::vec2 pos2 = shape->GetVertex(2);

						math::vec2 pos3 = shape->GetVertex(1);
						math::vec2 pos4 = shape->GetVertex(3);
						GREET_DEBUG("BOX2DLAYER",pos1," ", pos2, " ",pos3," ", pos4);
						// Check if the polygon is a rectangle
						if ((pos3.x == pos1.x || pos3.x == pos2.x) && (pos4.x == pos1.x || pos4.x == pos2.x))
						{
							if ((pos3.y == pos1.y || pos3.y == pos2.y) && (pos4.y == pos1.y || pos4.y == pos2.y))
							{
								math::Transform t = math::Transform().translate(bodies[i].GetPosition()+pos1).scale((pos1 - pos2).abs());
								push(new Renderable2D(t, 0xffffffff, NULL));
							}
						}
						
					}
				}


			}
		}

		void update(float timeElapsed) override
		{
			
		}

		void render() const override
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			Layer::render();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		}
	};
}}
