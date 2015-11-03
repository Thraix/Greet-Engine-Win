#pragma once

#include "entity.h"
#include <utils\physics.h>
#include "player.h"
#include "goal.h"

class Ball : public Entity
{
private:
	int m_occupied;
	std::vector<Goal*> m_goals;
	std::vector<Player*> m_players;
public:

private:
public:
	Ball(greet::graphics::Animation* animation, float x, float y, float width, float height);
	bool update(float timeElapsed) override;
	inline bool isOccupied(){ return m_occupied != -1; }
	inline int playerBall() { return m_occupied; }
	void setPlayers(std::vector<Player*> players);
	void setGoals(std::vector<Goal*> goals);

};