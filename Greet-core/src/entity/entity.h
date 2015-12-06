#pragma once

#include <math\maths.h>
#include <Box2D\Box2D.h>
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Dynamics\b2World.h>
#include <graphics\renderable2d.h>

namespace greet { namespace entity{
	class Entity : public graphics::Renderable2D
	{
	public:

		math::vec2 m_size;
		math::vec2 m_position;
		b2Body* m_body;

	public:
		Entity(math::vec2 position,math::vec2 size, uint color, graphics::Sprite* sprite,b2World* world);
		bool update(float timeElapsed);
		void createBody(math::vec2 pos, math::vec2 size, b2World* world);

		inline const math::vec2& getPosition() const { return m_position; }
		inline const math::vec2& getSize() const { return m_size; }
		inline const b2Body* getBody() const { return m_body; }
	};
}}