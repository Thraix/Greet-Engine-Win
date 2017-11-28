#pragma once

#include <Box2D/Box2D.h>
#include <graphics/layers/Layer.h>
#include <entity/Entity.h>
#include <graphics/Renderable2D.h>
#include <logging/Log.h>
#include <graphics/models/EntityModel.h>

namespace Greet {
	class Box2DLayer : public Layer
	{
	public:
		b2World* m_world;


	public:
		Box2DLayer(Shader* shader, mat3 projectionMatrix, b2World* world);

		void update(float timeElapsed) override;

		void render() const override;
	};
}
