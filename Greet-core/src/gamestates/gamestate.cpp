#include "gamestate.h"

namespace greet { namespace gamestate {
	GameState::GameState(graphics::Renderer2D* renderer, graphics::Shader* shader, math::mat3 projectionMatrix)
		: Layer(renderer,shader,projectionMatrix)
	{

	}
}}