#pragma once

#include <logging/logger.h>
#include <graphics/fonts/fontmanager.h>
#include <graphics/textures/texturemanager.h>
#include <audio/soundmanager.h>
#include <audio/channelmanager.h>
#include <graphics/textures/imagefactory.h>
#include <input/joystick.h>
#include <vector>
#include <iostream>
#include <internal/greetgl.h>
#include <internal/greet_types.h>
#include <utils/uuid.h>
#include <listeners/listeners.h>

#define MAX_KEYS			1024
#define MAX_MOUSEBUTTONS	4

#define BUTTON_STATE_PRESSED	0x0
#define BUTTON_STATE_RELEASED	0x1
#define BUTTON_STATE_DOWN		0x2
#define BUTTON_STATE_UP			0x3

#define JOYSTICK_STATE_DISCONNECTED 0x0
#define JOYSTICK_STATE_CONNECTED	0x1

namespace greet { namespace graphics {
	class GUI;
	typedef void(*WINDOW_RESIZE)(int width, int height);
	typedef void(*JOYSTICK_STATE)(uint joystick, unsigned char state);
	typedef void(*WINDOW_FOCUS)(int state); 


	class Window
	{
	private:
		static std::vector<listener::WindowResizeListener*> windowResize;
		static std::vector<listener::WindowFocusListener*> windowFocus;
		static std::vector<listener::JoystickStateListener*> joystickState;
		static void* pointer;
		friend struct GLFWwindow;
		static std::string title;
		static uint width, height;
		static GLFWwindow *window;
		static math::vec4 bgColor;

		static std::vector<input::Joystick> joysticks;
	
		static bool focus;
		
		static bool curKeys[MAX_KEYS];
		static bool pasKeys[MAX_KEYS];

		static bool curMouseButtons[MAX_MOUSEBUTTONS];
		static bool pasMouseButtons[MAX_MOUSEBUTTONS];
		static math::vec2 mousePos;
		static math::vec2 mousePosPixel;
	private:
		static bool init();
		static void window_resize(GLFWwindow *window, int width, int height);
		static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		static void window_focus_callback(GLFWwindow* window, int state);
		static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

		static void checkJoysticks();
	public:
		//Window(const char *title, int width, int height);
		//~Window();

		static void createWindow(std::string title, uint width, uint height);
		static void destroyWindow();

		static bool closed();
		static void clear();

		static void render();
		static void update();
		static void tick();

		static void setBackgroundColor(math::vec4 color);
		static void addResizeCallback(listener::WindowResizeListener* listenter);
		static void addWindowFocusCallback(listener::WindowFocusListener* listener);
		static void addJoystickCallback(listener::JoystickStateListener* listener);

		inline static math::vec4 getBackgroundColor() { return bgColor; }
		inline static int getWidth() { return width; };
		inline static int getHeight() { return height; };

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
		inline static math::vec2 getMousePos(math::mat3 transform) { return transform.inverse()*mousePos; }
		inline static float getMouseX(math::mat3 transform) { return (transform.inverse()*mousePos).x; }
		inline static float getMouseY(math::mat3 transform) { return (transform.inverse()*mousePos).y; }

		inline static math::vec2 getMousePosPixel() { return mousePosPixel; }
		inline static float getMouseXPixel() { return mousePosPixel.x; }
		inline static float getMouseYPixel() { return mousePosPixel.y; }
		inline static input::Joystick &getJoystick(uint joystick){ ASSERT(joystick < 4, "WINDOW","Invalid Joystick. Ranges from 0-3: ", joystick); return joysticks[joystick]; }
		inline static bool isJoystickConnected(uint joystick){ ASSERT(joystick < 4, "WINDOW", "Invalid Joystick. Ranges from 0-3: ", joystick); return joysticks[joystick].m_connected; }


		inline static void* getUserPointer(Window* window) { return window->pointer; }

		static void setUserPointer(Window* window, void* pointer);

	};
}}
