#include "Entity.h"

namespace Greet {


	Entity::Entity(const Vec2& position, const Vec2& size, uint color, b2World* world)
		: RenderablePoly(position,Math::B2Vec2ToVec2(Math::GetRectangle(size),4),4,color)
	{
		CreateBody(position, size, world);
	}

	Entity::~Entity()
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}

	bool Entity::Update(float timeElapsed)
	{
		m_position = m_body->GetPosition();
		Vec4 rectangle = Math::GetRectangle(m_body);
		if (rectangle.z != 0 && rectangle.w != 0)
		{
			//m_transform = Transform().translate(m_body->GetPosition()).rotateR(m_body->GetAngle()).translate(-rectangle.z / 2.0f, -rectangle.w / 2.0f).scale(rectangle.z, rectangle.w);
		}
		//return Renderable2D::update(timeElapsed);
		return false;
	}

	void Entity::CreateBody(Vec2 pos, Vec2 size, b2World* world)
	{
		b2BodyDef def;
		def.type = b2_dynamicBody;
		def.position.Set(pos.x, pos.y);
		def.userData = this;
		def.fixedRotation = true;
		m_body = world->CreateBody(&def);
		b2PolygonShape shape;
		shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 100.0f;
		fixtureDef.friction = 93.0f;
		m_body->CreateFixture(&fixtureDef);

	}
}
