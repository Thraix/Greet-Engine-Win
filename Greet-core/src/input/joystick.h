#pragma once

#include <vector>
#include <internal/greetgl.h>
#include <logging/logger.h>
#include <internal/greet_types.h>
#include <math/maths.h>

#ifndef MAX_JOYSTICKS 
	#define MAX_JOYSTICKS 4
#endif

namespace greet { namespace graphics{
	class Window;
}}

namespace greet { namespace input {

	class Joystick
	{

		friend class greet::graphics::Window;

	private:
		std::vector<uint> m_mapping;
		bool m_connected = false;
		bool m_wasConnected = false;
		//STORES THE JOYSTICK NUMBER
		const int m_jsNum;

		float m_calibrateLeft;
		float m_calibrateRight;

		//AXES
		math::vec2 m_leftStick;
		math::vec2 m_rightStick;

		bool buttonCur[GLFW_JOYSTICK_BUTTONS];
		bool buttonPas[GLFW_JOYSTICK_BUTTONS];

	private:
		Joystick(uint jsNum, float m_calibrateLeft, float m_calibrateRight);
		void update();
		bool checkConnect();
		void clearInput();
	public:

		inline math::vec2 getLeftStick() const { return m_leftStick; }
		inline math::vec2 getRightStick() const { return m_rightStick; }

		void remapButton(uint button, uint rebind);
		bool buttonExists(uint buttoncode) const;
		bool isButtonPressed(uint buttoncode) const;
		bool isButtonReleased(uint buttoncode) const;
		bool isButtonDown(uint buttoncode) const;
		bool isRealButtonPressed(uint buttoncode) const;
		bool isRealButtonReleased(uint buttoncode) const;
		bool isRealButtonDown(uint buttoncode) const;
		bool isConnected() const { return m_connected; }

	};
}}
