#pragma once

#include <math/Maths.h>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <graphics/RenderablePoly.h>
#include <math/MathFunc.h>

namespace Greet {

	class Entity : public RenderablePoly
	{
	public:

		vec2 m_size;
		b2Body* m_body;

	public:
		Entity(const vec2& position, const vec2& size, uint color, b2World* world);
		virtual ~Entity();
		bool update(float timeElapsed);
		void createBody(vec2 pos, vec2 size, b2World* world);

		inline const vec2& getPosition() const { return m_position; }
		inline const vec2& getSize() const { return m_size; }
		inline const b2Body* getBody() const { return m_body; }
	};
}
