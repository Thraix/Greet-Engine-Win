#pragma once

#include <utils/log.h>
#include <managers/fontmanager.h>
#include <managers/soundmanager.h>
#include <managers/channelmanager.h>
#include <input/joystick.h>
#include <vector>
#include <iostream>
#include <greetgl.h>
#include <greet_types.h>
#include <utils\uuid.h>
#include <listeners\listeners.h>

#define MAX_KEYS			1024
#define MAX_MOUSEBUTTONS	32

#define BUTTON_STATE_PRESSED	0x0
#define BUTTON_STATE_RELEASED	0x1
#define BUTTON_STATE_DOWN		0x2
#define BUTTON_STATE_UP			0x3

#define JOYSTICK_STATE_DISCONNECTED 0x0
#define JOYSTICK_STATE_CONNECTED	0x1

namespace greet { namespace graphics {
	class GUI;
	typedef void(*WINDOW_RESIZE)(Window* window, int width, int height);
	typedef void(*JOYSTICK_STATE)(Window* window, uint joystick, unsigned char state);
	typedef void(*WINDOW_FOCUS)(Window* window, int state); 


	class Window
	{
	private:
		std::vector<listener::WindowResizeListener*> f_windowResize;
		std::vector<listener::WindowFocusListener*> f_windowFocus;
		std::vector<listener::JoystickStateListener*> f_joystickState;
		void* m_pointer;
		friend struct GLFWwindow;
		const char *m_title;
		int m_width, m_height;
		GLFWwindow *m_window;
		math::vec4 m_bgColor = math::vec4(0.0f, 0.0f, 0.0f, 0.0f);

		static std::vector<input::Joystick> m_joysticks;
	
		bool m_focus;
		
		static bool m_curKeys[MAX_KEYS];
		static bool m_pasKeys[MAX_KEYS];

		static bool m_curMouseButtons[MAX_MOUSEBUTTONS];
		static bool m_pasMouseButtons[MAX_MOUSEBUTTONS];
		static math::vec2 m_mousePos;
	private:
		bool init();
		static void window_resize(GLFWwindow *window, int width, int height);
		static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		static void window_focus_callback(GLFWwindow* window, int state);
		static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	public:
		Window(const char *title, int width, int height);
		~Window();

		bool closed() const;
		void clear() const;

		void render();
		void update();
		void tick();

		void setBackgroundColor(math::vec4 color);
		void addResizeCallback(listener::WindowResizeListener* listenter);
		void addWindowFocusCallback(listener::WindowFocusListener* listener);
		void addJoystickCallback(listener::JoystickStateListener* listener);

		inline math::vec4 getBackgroundColor() const { return m_bgColor; }
		inline int getWidth() const { return m_width; };
		inline int getHeight() const { return m_height; };

		//Key functions
		static bool keyExists(uint keycode);
		static bool isKeyPressed(uint keycode);
		static bool isKeyReleased(uint keycode);
		static bool isKeyDown(uint keycode);

		//Mouse Button functions
		static bool mouseButtonExists(uint keycode);
		static bool isMouseButtonPressed(uint button);
		static bool isMouseButtonReleased(uint button);
		static bool isMouseButtonDown(uint button);

		//Mouse Positions
		inline static math::vec2 getMousePos() { return m_mousePos; }
		inline static float getMouseX(){ return m_mousePos.x; }
		inline static float getMouseY(){ return m_mousePos.y; }
		inline static input::Joystick &getJoystick(uint joystick){ GREET_ASSERT(joystick < 4, "WINDOW","Invalid Joystick. Ranges from 0-3: ", joystick); return m_joysticks[joystick]; }
		inline static bool isJoystickConnected(uint joystick){ GREET_ASSERT(joystick < 4, "WINDOW", "Invalid Joystick. Ranges from 0-3: ", joystick); return m_joysticks[joystick].m_connected; }


		inline static void* getUserPointer(Window* window) { return window->m_pointer; }

		static void setUserPointer(Window* window, void* pointer);

	};
}}