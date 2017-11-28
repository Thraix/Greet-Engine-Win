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

	inline float RoundDown(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		return ((int)(numToRound / multiple))*multiple;
	}

	inline float RoundUp(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float ans = ((int)(numToRound / multiple))*multiple;
		return ans < numToRound ? ans + multiple : ans;
	}

	inline float RoundClose(float numToRound, float multiple)
	{
		if (multiple == 0)
			return 0;
		float down = ((int)(numToRound / multiple))*multiple;
		float up = down < numToRound ? down + multiple : down;
		return (numToRound - down) < (up - numToRound) ? down : up;
	}

	inline bool IsPositive(float val)
	{
		return -val < val;
	}

	//struct Vec2;
	inline void Clamp(float* value, float min, float max)
	{
		if(min < max)
			*value = *value < min ? min : (*value > max ? max : *value);
		else
			*value = *value < max ? max : (*value > min ? min : *value);
	}

	// Returns half the value, removes one to value if it is odd.
	inline int Half(int value)
	{
		return (value - (value % 2)) / 2;
	}


	inline float ToRadians(float degrees)
	{
		return (float)(degrees * M_PI * 0.005555555f);
	}

	inline float ToDegrees(float radians)
	{
		return (float)(radians * 180.0f / M_PI);
	}

	inline Vec2* GetVertices(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			Vec2* vertices = new Vec2[shape->GetVertexCount()];
			for (uint i = 0; i < shape->GetVertexCount(); i++)
			{
				vertices[i] = Vec2(shape->GetVertex(i)).RotateR(body->GetAngle());
			}
			return vertices;
		}
		return NULL;
	}

	inline uint GetVertexCount(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			return shape->GetVertexCount();
		}
		return 0;
	}

	inline vec4 GetRectangle(b2Body* body)
	{
		const b2Fixture* f = body->GetFixtureList();
		uint i = 0;

		if (f->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
			if (shape->GetVertexCount() == 4)
			{
				Vec2 pos1 = shape->GetVertex(0);
				Vec2 pos2 = shape->GetVertex(2);

				Vec2 pos3 = shape->GetVertex(1);
				Vec2 pos4 = shape->GetVertex(3);

				// Check if the polygon is a rectangle
				if ((pos3.x == pos1.x || pos3.x == pos2.x) && (pos4.x == pos1.x || pos4.x == pos2.x))
				{
					if ((pos3.y == pos1.y || pos3.y == pos2.y) && (pos4.y == pos1.y || pos4.y == pos2.y))
					{
						Vec2 pos = body->GetPosition() + pos1;
						Vec2 size = (pos1 - pos2).Abs();
						return vec4(pos.x, pos.y, size.x, size.y);
					}
				}
			}
		}
		return vec4(0, 0, 0, 0);
	}

	inline b2Vec2* GetPoly(uint vertices, float size, bool min = true, float rotation = 0)
	{

		b2Vec2* triangle = new b2Vec2[vertices];
		float rad = 2 * M_PI / vertices;

		if (vertices % 2 == 0)
			rotation += rad / 2;
		if (!min)
			size = size / sin(M_PI * (vertices - 2) / (float)vertices / 2.0f);

		for (uint i = 0; i < vertices; i++)
		{
			Vec2 v = Vec2(0, -size).RotateR(rotation + rad*i);
			triangle[i] = b2Vec2(v.x, v.y);
		}
		return triangle;
	}

	inline b2Vec2* GetRectangle(const Vec2& size)
	{

		b2Vec2* rectangle = new b2Vec2[4];
		float rad = (float)(M_PI / 2.0);
		rectangle[0] = b2Vec2(-size.x/2.0f,-size.y/2.0f);
		rectangle[1] = b2Vec2(+size.x/2.0f,-size.y/2.0f);
		rectangle[2] = b2Vec2(+size.x/2.0f,+size.y/2.0f);
		rectangle[3] = b2Vec2(-size.x/2.0f,+size.y/2.0f);
		return rectangle;
	}

	inline Vec2* B2Vec2ToVec2(b2Vec2* vecs, uint vertexCount)
	{
		Vec2* vec = new Vec2[vertexCount];

		for (uint i = 0; i < vertexCount; i++)
		{
			vec[i] = Vec2(vecs[i]);
		}
		return vec;
	}
}}
