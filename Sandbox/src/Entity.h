#pragma once

#include <graphics\animation.h>
#include <graphics\renderable2d.h>

class Entity : public greet::graphics::Renderable2D
{

protected:
	greet::math::vec2 m_vel;
public:

private:
	void dash();
	void move();

public:



	Entity(greet::graphics::Animation* animation, float x, float y, float width, float height)
		: greet::graphics::Renderable2D(greet::math::vec2(x, y), greet::math::vec2(width, height), 0xffffffff,animation)
	{
	}

	~Entity()
	{
	}

	virtual bool update(float timeElapsed) override
	{
		return m_sprite->update(timeElapsed);
	}
};