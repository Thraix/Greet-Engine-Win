#pragma once

#include <Box2D/Box2D.h>
#include <graphics/layers/Layer.h>
#include <entity/Entity.h>
#include <graphics/Renderable2D.h>
#include <logging/Log.h>
#include <graphics/models/EntityModel.h>
#include <graphics/renderers/BatchRenderer.h>

namespace Greet {
	class Box2DLayer : public Layer
	{
	public:
		b2World* m_world;


	public:
		Box2DLayer(Shader* shader, Mat3 projectionMatrix, b2World* world);

		void Update(float timeElapsed) override;

		void Render() const override;
	};
}
