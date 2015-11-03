#include "ball.h"
#include "player.h"
#include "goal.h"

Ball::Ball(greet::graphics::Animation* animation, float x, float y, float width, float height)
	: Entity(animation, x, y, width, height)
{
	m_occupied = -1;
}

bool Ball::update(float timeElapsed)
{
	using namespace greet;
	if (isOccupied())
	{
		m_pos = m_players[m_occupied]->m_pos + m_players[m_occupied]->m_size/2.0f-m_size/2.0f;
	}
	else
	{
		uint size = m_players.size();
		for (uint i = 0; i < size; i++)
		{
			Player* player = m_players[i];
			if (Physics::Collision(player->m_pos,player->m_size,m_pos,m_size))
			{
				m_occupied = i;
				break;
			}
		}
	}
	return false;
}

void Ball::setPlayers(std::vector<Player*> players)
{
	m_players = players;
}
void Ball::setGoals(std::vector<Goal*> goals)
{
	m_goals = goals;
}