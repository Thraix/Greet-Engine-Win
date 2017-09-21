#pragma once

#include <vector>
#include <gamestates/gamestate.h>
#include <logging/log.h>
#include <internal/Greet_types.h>

namespace Greet {
	class GameStateManager
	{
	private:
		static GameState* m_gamestate;
	public:
		static void set(GameState* gamestate);
		static void render();
		static void update(float timeElapsed);
		static GameState* get() { return m_gamestate; }
		static void goBack();
		static void destroy();
	private:
		GameStateManager(){}
	};
}