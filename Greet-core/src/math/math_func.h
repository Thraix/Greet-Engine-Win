#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <math/vec4.h>
#include <math/vec2.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <internal/greet_types.h>
#include <iostream>


namespace greet{ namespace math{

	//struct vec2;
	inline void clamp(float* value, float min, float max)
	{
		*value = *value < min ? min : (*value > max ? max : *value);
	}


	inline float toRadians(float degrees)
	{
		return (float)(degrees * M_PI * 0.005555555f);
	}

	inline vec2* getVertices(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			vec2* vertices = new vec2[shape->GetVertexCount()];
			for (uint i = 0; i < shape->GetVertexCount(); i++)
			{
				vertices[i] = math::vec2(shape->GetVertex(i)).rotateR(body->GetAngle());
			}
			return vertices;
		}
		return NULL;
	}

	inline uint getVertexCount(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			return shape->GetVertexCount();
		}
		return 0;
	}

	inline vec4 getRectangle(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();
		uint i = 0;

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			if (shape->GetVertexCount() == 4)
			{
				math::vec2 pos1 = shape->GetVertex(0);
				math::vec2 pos2 = shape->GetVertex(2);

				math::vec2 pos3 = shape->GetVertex(1);
				math::vec2 pos4 = shape->GetVertex(3);

				// Check if the polygon is a rectangle
				if ((pos3.x == pos1.x || pos3.x == pos2.x) && (pos4.x == pos1.x || pos4.x == pos2.x))
				{
					if ((pos3.y == pos1.y || pos3.y == pos2.y) && (pos4.y == pos1.y || pos4.y == pos2.y))
					{
						math::vec2 pos = body->GetPosition() + pos1;
						math::vec2 size = (pos1 - pos2).abs();
						return math::vec4(pos.x, pos.y, size.x, size.y);
					}
				}
			}
		}
		return math::vec4(0, 0, 0, 0);
	}

	inline b2Vec2* getPoly(uint vertices, float size, bool min = true, float rotation = 0)
	{

		b2Vec2* triangle = new b2Vec2[vertices];
		float rad = 2 * M_PI / vertices;

		if (vertices % 2 == 0)
			rotation += rad / 2;
		if (!min)
			size = size / sin(M_PI * (vertices - 2) / (float)vertices / 2.0f);

		for (uint i = 0; i < vertices; i++)
		{
			math::vec2 v = math::vec2(0, -size).rotateR(rotation + rad*i);
			triangle[i] = b2Vec2(v.x, v.y);
		}
		return triangle;
	}

	inline b2Vec2* getRectangle(const math::vec2& size)
	{

		b2Vec2* rectangle = new b2Vec2[4];
		float rad = (float)(M_PI / 2.0);
		rectangle[0] = b2Vec2(-size.x/2.0f,-size.y/2.0f);
		rectangle[1] = b2Vec2(+size.x/2.0f,-size.y/2.0f);
		rectangle[2] = b2Vec2(+size.x/2.0f,+size.y/2.0f);
		rectangle[3] = b2Vec2(-size.x/2.0f,+size.y/2.0f);
		return rectangle;
	}

	inline vec2* b2Vec2ToVec2(b2Vec2* vecs, uint vertexCount)
	{
		vec2* vec = new vec2[vertexCount];

		for (uint i = 0; i < vertexCount; i++)
		{
			vec[i] = math::vec2(vecs[i]);
		}
		return vec;
	}
}}
