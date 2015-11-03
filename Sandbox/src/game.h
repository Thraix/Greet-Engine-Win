#pragma once

#include <gamestates\gamestate.h>

#include "ball.h"
#include <graphics\shaders\shaderfactory.h>
#include <graphics\batchrenderer2d.h>
#include <graphics\label.h>

class Game : public greet::gamestate::GameState
{
private:
	std::vector<Player*> m_players;
	std::vector<Goal*> m_goals;
	Ball* m_ball;
	int m_player;
	bool didPause;

	greet::graphics::Layer m_uilayer;
	greet::graphics::Label m_score;
	greet::graphics::Label m_noPlayers;
public:

private:
	void init() override;
	void renderAfter() override;
	void update(float timeElapsed) override;
	uint playersConnected();
public:
	Game(int players);
	~Game();
};