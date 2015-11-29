#include "game.h"
#include <managers\atlasmanager.h>


Game::Game(int players) :
	GameState(new greet::graphics::BatchRenderer2D(), greet::graphics::ShaderFactory::GradientShader(), greet::math::mat3::orthographic(-32, 32, -18, 18)),
	m_ball(new Ball(new greet::graphics::Animation(0xffffffff), -0.5f, -0.5f, 1, 1)),
	m_player(players),
	m_uilayer(new greet::graphics::BatchRenderer2D(), greet::graphics::ShaderFactory::LEDShader(), greet::math::mat3::orthographic(0, 960 / 2.0f, 0, 540 / 2.0f)),
	m_score("0 : 0", "default", greet::math::vec2(480 / 2.0f, 0), 0xffff00ff, 32),
	m_noPlayers("Not enough players in game.", "default", greet::math::vec2(480 / 2.0f, 270 / 2.0f), 0xffffff00, 16)
{

}

Game::~Game()
{
	delete m_ball;
	for (uint i = 0; i < m_player; i++)
		delete m_players[i];
	
	uint size = m_goals.size();
	for (uint i = 0; i < size; i++)
		delete m_players[i];
}

void Game::init()
{
	using namespace greet;
	
	m_score.centerTextX();
	m_noPlayers.centerTextX();
	m_uilayer.push(&m_score);
	m_uilayer.push(&m_noPlayers);
	int height = 10;
	m_goals.push_back(new Goal(new graphics::Animation(*managers::AtlasManager::get("atlas32")->getSpriteFromSheet("animation", math::vec2(0, 2 / 4.0f), math::vec2(1 / 4.0f, 2 / 4.0f)), 1, 1, true), -32, -height / 2.0f, height / 2.0f, height));
	m_goals.push_back(new Goal(new graphics::Animation(0xffff00ff), 32 - height / 2.0f, -height / 2.0f, height / 2.0f, height));
	push(m_goals[0]);
	push(m_goals[1]);

	if (m_player == 2)
	{
		m_players.push_back(new Player(new graphics::Animation(0xffff0000), -26, -1, 2, 2, m_ball, 0));
		m_players.push_back(new Player(new graphics::Animation(0xff00ff00), 24, -1, 2, 2, m_ball, 1));
		push(m_players[0]);
		push(m_players[1]);
	}
	m_ball->setPlayers(m_players);
	m_ball->setGoals(m_goals);
	push(m_ball);

}

void Game::renderAfter()
{
	m_uilayer.render();
}

void Game::update(float timeElapsed)
{
	m_noPlayers.render = false;
	if (!m_noPlayers.render)
	{
		for (int i = 0; i < m_player; i++)
		{
			m_players[i]->update(timeElapsed);
		}

		for (int i = 0; i < 2; i++)
		{
			m_goals[i]->update(timeElapsed);
		}
		m_ball->update(timeElapsed);
	}
}

uint Game::playersConnected()
{
	using namespace greet;
	using namespace graphics;
	uint var = 0;
	for (int i = 0; i < m_player; i++)
	{
		if (Window::getJoystick(i).isConnected())
			var++;
	}
	return var;
}