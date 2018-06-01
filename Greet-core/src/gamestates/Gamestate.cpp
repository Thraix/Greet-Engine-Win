#include "Gamestate.h"

namespace Greet {
	GameState::GameState(Renderer2D* renderer, const Shader& shader, Mat3 projectionMatrix)
		: Layer(renderer,shader,projectionMatrix)
	{

	}
}