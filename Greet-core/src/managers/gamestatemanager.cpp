#include "gamestatemanager.h"

namespace greet{ namespace managers {

	gamestate::GameState* GameStateManager::m_gamestate;

	void GameStateManager::set(gamestate::GameState* gamestate)
	{
		if (m_gamestate!=nullptr)
			gamestate->parent = m_gamestate;
		m_gamestate = gamestate;
		m_gamestate->init();
	}

	void GameStateManager::render()
	{
		m_gamestate->renderBefore();
		m_gamestate->render();
		m_gamestate->renderAfter();
	}

	void GameStateManager::update(float timeElapsed)
	{
		m_gamestate->update(timeElapsed);
	}

	void GameStateManager::goBack()
	{
		if (m_gamestate->parent != nullptr)
		{
			gamestate::GameState* state = m_gamestate->parent;
			delete m_gamestate;
			m_gamestate = state;
		}
	}

	void GameStateManager::destroy()
	{
		delete m_gamestate;
	}

}}