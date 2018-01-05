#include "Gamestate.h"

namespace Greet {
	GameState::GameState(BatchRenderer2D* renderer, Shader* shader, Mat3 projectionMatrix)
		: Layer(renderer,shader,projectionMatrix)
	{

	}
}