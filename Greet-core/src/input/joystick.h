#pragma once

#include <vector>
#include <internal/GreetGL.h>
#include <logging/Log.h>
#include <internal/GreetTypes.h>
#include <math/Maths.h>
#include <utils/Timer.h>

#ifndef MAX_JOYSTICKS 
	#define MAX_JOYSTICKS 4
#endif


namespace Greet {

	class Joystick
	{

		friend class Window;

	private:
		std::vector<uint> m_mapping;
		bool m_connected = false;
		bool m_wasConnected = false;
		//STORES THE JOYSTICK NUMBER
		const int m_jsNum;

		float m_calibrateLeft;
		float m_calibrateRight;

		//AXES
		vec2 m_leftStick;
		vec2 m_rightStick;

		bool buttonCur[GLFW_JOYSTICK_BUTTONS];
		bool buttonPas[GLFW_JOYSTICK_BUTTONS];

	private:
		Joystick(uint jsNum, float m_calibrateLeft, float m_calibrateRight);
		void update();
		bool checkConnect();
		void clearInput();
	public:

		inline vec2 getLeftStick() const { return m_leftStick; }
		inline vec2 getRightStick() const { return m_rightStick; }

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
}
