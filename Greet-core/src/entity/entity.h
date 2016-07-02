#pragma once

#include <math/maths.h>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <graphics/renderablepoly.h>
#include <math/math_func.h>

namespace greet { namespace entity{

	class Entity : public graphics::RenderablePoly
	{
	public:

		math::vec2 m_size;
		b2Body* m_body;

	public:
		Entity(const math::vec2& position, const math::vec2& size, uint color, b2World* world);
		virtual ~Entity();
		bool update(float timeElapsed);
		void createBody(math::vec2 pos, math::vec2 size, b2World* world);

		inline const math::vec2& getPosition() const { return m_position; }
		inline const math::vec2& getSize() const { return m_size; }
		inline const b2Body* getBody() const { return m_body; }
	};
}}
