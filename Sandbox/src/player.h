#pragma once

#include "entity.h"
#include <input\joystick.h>
#include <graphics\window.h>

class Ball;

class Player : public Entity
{
private:
	Ball* m_ball;
	uint m_joystickIndex;
	bool m_dashing;
private:
	void dash();
public:

	Player(greet::graphics::Animation* animation, float x, float y, float width, float height, Ball* ball, uint joystickIndex);
	bool update(float timeElapsed) override;
	void move();
	inline bool isConnected() const { return greet::graphics::Window::getJoystick(m_joystickIndex).isConnected(); }
	inline bool isDashing() const { return m_dashing; }
};