#include "Gamestate.h"

namespace Greet {
	GameState::GameState(Renderer2D* renderer, Shader* shader, mat3 projectionMatrix)
		: Layer(renderer,shader,projectionMatrix)
	{

	}
}