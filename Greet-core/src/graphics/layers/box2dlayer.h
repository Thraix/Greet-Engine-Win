#pragma once

#include <Box2D/Box2D.h>
#include <graphics/layers/layer.h>
#include <entity/entity.h>
#include <graphics/renderable2d.h>
#include <logging/log.h>
#include <graphics/renderers/batchrenderer.h>

namespace greet { namespace graphics {
	class Box2DLayer : public Layer
	{
	public:
		b2World* m_world;


	public:
		Box2DLayer(Shader* shader, math::mat3 projectionMatrix, b2World* world);

		void update(float timeElapsed) override;

		void render() const override;
	};
}}
