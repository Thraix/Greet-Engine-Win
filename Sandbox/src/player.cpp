#include "player.h"
#include "ball.h"

Player::Player(greet::graphics::Animation* animation, float x, float y, float width, float height, Ball* ball, uint joystickIndex)
	: Entity(animation, x, y, width, height), m_ball(ball), m_joystickIndex(joystickIndex)
{
	using namespace greet::graphics;
	using namespace greet;
	m_vel = math::vec2(0, 0);
	Window::getJoystick(joystickIndex).remapButton(GLFW_JOYSTICK_A, GLFW_JOYSTICK_B);
	Window::getJoystick(joystickIndex).remapButton(GLFW_JOYSTICK_A, GLFW_JOYSTICK_X);
	Window::getJoystick(joystickIndex).remapButton(GLFW_JOYSTICK_A, GLFW_JOYSTICK_Y);
}

void Player::dash()
{
	m_vel.normalize();
	m_dashing = true;
}

bool Player::update(float timeElapsed)
{

	using namespace greet::graphics;
	m_sprite->update(timeElapsed);

	move();

	if (!m_dashing)
	{
		if (Window::getJoystick(m_joystickIndex).isButtonPressed(GLFW_JOYSTICK_A))
		{
			dash();
		}
	}

	//m_vel = greet::math::vec2(0.1f, 0);
	m_pos += m_vel;
	return false;

}

void Player::move()
{
	using namespace greet;

	const float maxSpeed = 0.2f;
	const float maxSpeedSQ = maxSpeed * maxSpeed;
	const float acc = 0.05f;

	math::vec2 jsVel = graphics::Window::getJoystick(m_joystickIndex).getLeftStick();

	math::vec2 velDif = jsVel * maxSpeed - m_vel;
	
	m_vel += velDif*acc;
	if (m_vel.lengthSQ() > maxSpeedSQ&&!m_dashing)
	{
		m_vel.normalize()*=maxSpeed;
	}
	else if (m_dashing&&m_vel.lengthSQ() < maxSpeed + 0.1f)
	{
		m_dashing = false;
	}
}