#include "entity.h"

namespace greet { namespace entity {


	Entity::Entity(math::vec2 position, math::vec2 size,b2World* world)
		: m_position(position),m_size(size)
	{
		createBody(position, size, world);
	}

	void Entity::update(float timeElapsed)
	{
		m_position = m_body->GetPosition();
	}

	const void Entity::createBody(math::vec2 pos, math::vec2 size, b2World* world)
	{
		b2BodyDef def;
		def.type = b2_dynamicBody;
		def.position.Set(pos.x, pos.y);
		def.userData = this;
		m_body = world->CreateBody(&def);
		b2PolygonShape shape;
		shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&fixtureDef);
	}
}}