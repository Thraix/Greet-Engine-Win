#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <math/vec4.h>
#include <math/vec2.h>
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Dynamics\b2Fixture.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>
#include <greet_types.h>
#include <iostream>


namespace greet{ namespace math{

	//struct vec2;

	inline float toRadians(float degrees)
	{
		return degrees * ((float)M_PI / 180.0f);
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
}}