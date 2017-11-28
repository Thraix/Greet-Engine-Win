#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <math/Vec4.h>
#include <math/Vec2.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <internal/GreetTypes.h>
#include <iostream>


namespace Greet{ namespace Math {

	inline float roundDown(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		return ((int)(numToRound / multiple))*multiple;
	}

	inline float roundUp(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float ans = ((int)(numToRound / multiple))*multiple;
		return ans < numToRound ? ans + multiple : ans;
	}

	inline float roundClose(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float down = ((int)(numToRound / multiple))*multiple;
		float up = down < numToRound ? down + multiple : down;
		return (numToRound - down) < (up - numToRound) ? down : up;
	}

	inline bool isPositive(float val)
	{
		return -val < val;
	}

	//struct vec2;
	inline void clamp(float* value, float min, float max)
	{
		if(min < max)
			*value = *value < min ? min : (*value > max ? max : *value);
		else
			*value = *value < max ? max : (*value > min ? min : *value);
	}

	// Returns half the value, removes one to value if it is odd.
	inline int half(int value)
	{
		return (value - (value % 2)) / 2;
	}


	inline float toRadians(float degrees)
	{
		return (float)(degrees * M_PI * 0.005555555f);
	}

	inline float toDegrees(float radians)
	{
		return (float)(radians * 180.0f / M_PI);
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
				vertices[i] = vec2(shape->GetVertex(i)).rotateR(body->GetAngle());
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
				vec2 pos1 = shape->GetVertex(0);
				vec2 pos2 = shape->GetVertex(2);

				vec2 pos3 = shape->GetVertex(1);
				vec2 pos4 = shape->GetVertex(3);

				// Check if the polygon is a rectangle
				if ((pos3.x == pos1.x || pos3.x == pos2.x) && (pos4.x == pos1.x || pos4.x == pos2.x))
				{
					if ((pos3.y == pos1.y || pos3.y == pos2.y) && (pos4.y == pos1.y || pos4.y == pos2.y))
					{
						vec2 pos = body->GetPosition() + pos1;
						vec2 size = (pos1 - pos2).abs();
						return vec4(pos.x, pos.y, size.x, size.y);
					}
				}
			}
		}
		return vec4(0, 0, 0, 0);
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
			vec2 v = vec2(0, -size).rotateR(rotation + rad*i);
			triangle[i] = b2Vec2(v.x, v.y);
		}
		return triangle;
	}

	inline b2Vec2* getRectangle(const vec2& size)
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
			vec[i] = vec2(vecs[i]);
		}
		return vec;
	}
}}
