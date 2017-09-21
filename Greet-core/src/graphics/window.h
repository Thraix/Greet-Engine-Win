#pragma once

#include <logging/log.h>
#include <graphics/fonts/fontmanager.h>
#include <graphics/textures/texturemanager.h>
#include <graphics/textures/texture2d.h>
#include <audio/soundmanager.h>
#include <audio/audiochannelmanager.h>
#include <graphics/textures/imagefactory.h>
#include <input/joystick.h>
#include <vector>
#include <iostream>
#include <internal/Greetgl.h>
#include <internal/Greet_types.h>
#include <utils/uuid.h>
#include <listeners\joystickstate.h>
#include <listeners\windowlistener.h>
#include <event\eventdispatcher.h>
#include <algorithm>

#define MAX_KEYS			1024
#define MAX_MOUSEBUTTONS	32

#define BUTTON_STATE_PRESSED	0x0
#define BUTTON_STATE_RELEASED	0x1
#define BUTTON_STATE_DOWN		0x2
#define BUTTON_STATE_UP			0x3

#define JOYSTICK_STATE_DISCONNECTED 0x0
#define JOYSTICK_STATE_CONNECTED	0x1

namespace Greet {
	class GUI;
	typedef void(*WINDOW_RESIZE)(int width, int height);
	typedef void(*JOYSTICK_STATE)(uint joystick, unsigned char state);
	typedef void(*WINDOW_FOCUS)(int state); 


	class Window
	{
	private:
		static std::vector<WindowResizeListener*> windowResize;
		static std::vector<WindowFocusListener*> windowFocus;
		static std::vector<JoystickStateListener*> joystickState;
		static void* pointer;
		friend struct GLFWwindow;
		static std::string title;
		static uint width, height;
		static GLFWwindow *window;
		static vec4 bgColor;

		static std::vector<Joystick> joysticks;
	
		static bool focus;
		static bool mouseButtonDown[MAX_MOUSEBUTTONS];
		static bool isMouseButtonDown;
		static vec2 mousePos;
		static vec2 mousePosPixel;
		static uint joystickCheck;
	private:
		static bool init();

		static void window_resize(GLFWwindow *window, int width, int height);
		static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void key_char_callback(GLFWwindow* window, uint charCode);

		static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		static void window_focus_callback(GLFWwindow* window, int state);
		static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_scroll_callback(GLFWwindow* window, double scrollX, double scrollY);

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

		static void setBackgroundColor(vec4 color);
		static void addResizeCallback(WindowResizeListener* listenter);
		static void removeResizeCallback(WindowResizeListener* listener);
		static void addWindowFocusCallback(WindowFocusListener* listener);
		static void removeWindowFocusCallback(WindowFocusListener* listener);
		static void addJoystickCallback(JoystickStateListener* listener);
		static void removeJoystickCallback(JoystickStateListener* listener);

		inline static vec4 getBackgroundColor() { return bgColor; }
		inline static int getWidth() { return width; };
		inline static int getHeight() { return height; };
		inline static void setTitle(const std::string& title) { glfwSetWindowTitle(window,title.c_str()); }

		//Mouse Positions
		inline static vec2 getMousePos(mat3 transform) { return transform.inverse()*mousePos; }
		inline static float getMouseX(mat3 transform) { return (transform.inverse()*mousePos).x; }
		inline static float getMouseY(mat3 transform) { return (transform.inverse()*mousePos).y; }

		inline static vec2 getMousePosPixel() { return mousePosPixel; }
		inline static float getMouseXPixel() { return mousePosPixel.x; }
		inline static float getMouseYPixel() { return mousePosPixel.y; }
		inline static Joystick &getJoystick(uint joystick){ ASSERT(joystick < GLFW_JOYSTICKS, "WINDOW","Invalid Joystick. Ranges from 0-3: ", joystick); return joysticks[joystick]; }
		inline static bool isJoystickConnected(uint joystick){ ASSERT(joystick < GLFW_JOYSTICKS, "WINDOW", "Invalid Joystick. Ranges from 0-3: ", joystick); return joysticks[joystick].m_connected; }


		inline static void* getUserPointer(Window* window) { return window->pointer; }

		static void setUserPointer(Window* window, void* pointer);

	};
}
