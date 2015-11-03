#pragma once

#include "entity.h"

class Ball;

class Goal : public Entity
{
private:

public:

private:

public:
	Goal(greet::graphics::Animation* animation, float x, float y, float width, float height);
	bool update(float timeElapsed) override;
};