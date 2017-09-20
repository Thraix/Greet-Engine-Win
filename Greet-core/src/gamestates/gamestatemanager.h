#pragma once

#include <vector>
#include <gamestates/gamestate.h>
#include <logging/log.h>
#include <internal/greet_types.h>

namespace greet { namespace gamestate {
	class GameStateManager
	{
	private:
		static gamestate::GameState* m_gamestate;
	public:
		static void set(gamestate::GameState* gamestate);
		static void render();
		static void update(float timeElapsed);
		static gamestate::GameState* get() { return m_gamestate; }
		static void goBack();
		static void destroy();
	private:
		GameStateManager(){}
	};
} }
