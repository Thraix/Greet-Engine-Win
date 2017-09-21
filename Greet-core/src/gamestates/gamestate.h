#pragma once

#include <graphics/layers/layer.h>

namespace Greet {
	class GameState : public Layer
	{
	friend class GameStateManager;
	protected:
		GameState* parent;
	public:

	protected:
		virtual void init() = 0;
		virtual void setUniforms(){}
		virtual void renderBefore(){};
		virtual void renderAfter(){};
		virtual void update(float timeElapsed) = 0;

	public:
		GameState(Renderer2D* renderer, Shader* shader, mat3 projectionMatrix);
		virtual ~GameState(){ }
	};
}
