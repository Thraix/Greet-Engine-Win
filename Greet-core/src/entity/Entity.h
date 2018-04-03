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

		Vec2 m_size;
		b2Body* m_body;

	public:
		Entity(const Vec2& position, const Vec2& size, uint color, b2World* world);
		virtual ~Entity();
		bool Update(float timeElapsed);
		void CreateBody(Vec2 pos, Vec2 size, b2World* world);

		inline const Vec2& GetPosition() const { return m_position; }
		inline const Vec2& GetSize() const { return m_size; }
		inline const b2Body* GetBody() const { return m_body; }
	};
}
