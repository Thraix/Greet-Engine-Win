#pragma once

#include <graphics\layers\layer.h>

namespace greet { namespace managers { class GameStateManager; } }

namespace greet { namespace gamestate {
	class GameState : public graphics::Layer
	{
	friend managers::GameStateManager;
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
		GameState(graphics::Renderer2D* renderer, graphics::Shader* shader, math::mat3 projectionMatrix);
		virtual ~GameState(){ }
	};
}}