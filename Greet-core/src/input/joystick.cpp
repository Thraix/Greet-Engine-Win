#include "Joystick.h"

namespace Greet {
	Joystick::Joystick(uint jsNum, float calibrateLeft, float calibrateRight)
		: m_jsNum(jsNum), m_calibrateLeft(calibrateLeft), m_calibrateRight(calibrateRight)
	{
		clearInput();
		m_connected = false;
		m_wasConnected = false;
		for (uint i = 0; i < GLFW_JOYSTICK_BUTTONS; i++)
		{
			m_mapping.push_back(i);
		}
	}

	void Joystick::update()
	{
		m_wasConnected = m_connected;
		if (m_connected)
		{
			int count;
			const float* axes = glfwGetJoystickAxes(m_jsNum, &count);
			if (count == 0)
			{
				m_connected = false;
				clearInput();
				return;
			}
			ASSERT((count == GLFW_JOYSTICK_AXES), "CONTROLLER NOT SUPPORTED. INVALID AMOUNT OF AXES, found ", count, ", wanted ", GLFW_JOYSTICK_AXES, ".");
			m_leftStick = vec2(axes[0], axes[1]);
			if (m_leftStick.length()<m_calibrateLeft)
				m_leftStick = vec2(0, 0);

			m_rightStick = vec2(axes[3], axes[4]);
			if (m_rightStick.length()<m_calibrateRight)
				m_rightStick = vec2(0, 0);

			const unsigned char* buttons = glfwGetJoystickButtons(m_jsNum,&count);
			if (count == 0)
			{
				m_connected = false;
				clearInput();
				return;
			}
			ASSERT((count == GLFW_JOYSTICK_BUTTONS), "CONTROLLER NOT SUPPORTED. INVALID AMOUNT OF BUTTONS, found ", count, ", wanted ", GLFW_JOYSTICK_BUTTONS, ".");

			for (int i = 0; i < GLFW_JOYSTICK_BUTTONS;i++)
			{
				buttonPas[i] = buttonCur[i];
				buttonCur[i] = buttons[i]==GLFW_PRESS;
			}
		}
	}

	void Joystick::remapButton(uint button, uint rebind)
	{
		
		uint b = m_mapping[button];
		for (int i = 0; i < GLFW_JOYSTICK_BUTTONS; i++)
		{
			if (m_mapping[i] == rebind)
			{
				m_mapping[i] = button;
				break;
			}
		}
		m_mapping[button] = rebind;
	}
	bool Joystick::checkConnect()
	{
		m_wasConnected = m_connected;
		m_connected = glfwJoystickPresent(m_jsNum);
		return m_connected;
	}

	void Joystick::clearInput()
	{
		memset(buttonPas, false, GLFW_JOYSTICK_BUTTONS);
		memset(buttonCur, false, GLFW_JOYSTICK_BUTTONS);
		m_leftStick = vec2(0, 0);
		m_rightStick = vec2(0, 0);
	}

	bool Joystick::buttonExists(uint buttoncode) const
	{
		if (buttoncode >= GLFW_JOYSTICK_BUTTONS)
		{
			Log::error("Joystick button could not be found: ", buttoncode);
			return false;
		}
		return true;
	}

	bool Joystick::isButtonPressed(uint buttoncode) const
	{
		buttoncode = m_mapping[buttoncode];
		if (buttonExists(buttoncode))
			return buttonCur[buttoncode] && !buttonPas[buttoncode];
		return false;
	}

	bool Joystick::isButtonReleased(uint buttoncode) const
	{
		buttoncode = m_mapping[buttoncode];
		if (buttonExists(buttoncode))
			return !buttonCur[buttoncode] && buttonPas[buttoncode];
		return false;
	}

	bool Joystick::isButtonDown(uint buttoncode) const
	{
		buttoncode = m_mapping[buttoncode];
		if (buttonExists(buttoncode))
			return buttonCur[buttoncode];
		return false;
	}

	bool Joystick::isRealButtonPressed(uint buttoncode) const
	{
		if (buttonExists(buttoncode))
			return buttonCur[buttoncode] && !buttonPas[buttoncode];
		return false;
	}

	bool Joystick::isRealButtonReleased(uint buttoncode) const
	{
		if (buttonExists(buttoncode))
			return !buttonCur[buttoncode] && buttonPas[buttoncode];
		return false;
	}

	bool Joystick::isRealButtonDown(uint buttoncode) const
	{
		if (buttonExists(buttoncode))
			return buttonCur[buttoncode];
		return false;
	}
}
