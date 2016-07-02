#include "window.h"

namespace greet { namespace graphics {

	using namespace listener;

	std::vector<input::Joystick> Window::joysticks;
	bool Window::focus;
	bool Window::curKeys[MAX_KEYS];
	bool Window::curMouseButtons[MAX_MOUSEBUTTONS];
	bool Window::pasKeys[MAX_KEYS];
	bool Window::pasMouseButtons[MAX_MOUSEBUTTONS];
	math::vec2 Window::mousePos;
	math::vec2 Window::mousePosPixel;
	uint Window::width;
	uint Window::height;
	std::string Window::title;
	GLFWwindow *Window::window;
	math::vec4 Window::bgColor;


	std::vector<listener::WindowResizeListener*> Window::windowResize;
	std::vector<listener::WindowFocusListener*> Window::windowFocus;
	std::vector<listener::JoystickStateListener*> Window::joystickState;

	void Window::createWindow(std::string title, uint width, uint height)
	{
		bgColor = math::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		focus = true;
		Window::title = title;
		Window::width = width;
		Window::height = height;

		audio::SoundManager::init();
		memset(curKeys, false, MAX_KEYS);
		memset(pasKeys, false, MAX_KEYS);
		memset(curMouseButtons, false, MAX_MOUSEBUTTONS);
		memset(curMouseButtons, false, MAX_MOUSEBUTTONS);

		for (int i = 0; i < MAX_JOYSTICKS; i++)
		{
			joysticks.push_back(input::Joystick(i, 0.3f, 0.3f));
		}
		if (!init())
		{
			glfwTerminate();
		}
	}

	void Window::destroyWindow()
	{
		FontManager::destroy();
		audio::ChannelManager::destroy();
		audio::SoundManager::destroy();
		TextureManager::destroy();
		utils::UUID::cleanUp();
		glfwTerminate();
	}

	bool Window::init()
	{
		ASSERT(glfwInit(),"Failed to initialize GLFW!");
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		ASSERT(window,"Failed to initialize window!");
		//glfwSetInputMode(m_window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwMakeContextCurrent(window);

		//glfwSetWindowUserPointer(window,this);

		glfwSetFramebufferSizeCallback(window, window_resize);
		glfwSetKeyCallback(window,key_callback);
		glfwSetMouseButtonCallback(window,mouse_button_callback);
		glfwSetCursorPosCallback(window,mouse_position_callback);
		glfwSetWindowFocusCallback(window,window_focus_callback);
		glfwSwapInterval(0);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ASSERT(glewInit() == GLEW_OK,"Glew failed to init.");

		// SET DEFAULT VALUES
		FontManager::add(new Font("Roboto-Black.ttf","roboto-bold",72));
		FontManager::add(new Font("Roboto-thin.ttf","roboto",72));
		uint width,height,bpp;
		TextureManager::add(new Texture("frame.png","frame"));
		utils::UUID::init();

		LOG_INFO("WINDOW", "OpenGL Version: ", glGetString(GL_VERSION));
		LOG_INFO("WINDOW", "GLFW Version:   ", glfwGetVersionString());
		checkJoysticks();
		return true;
	}

	bool Window::keyExists(uint keycode)
	{
		if (keycode >= MAX_KEYS)
		{
			LOG_WARNING("WINDOW", "Key could not be found: ", keycode);
			return false;
		}
		return true;
	}

	bool Window::isKeyPressed(uint keycode)
	{
		if (keyExists(keycode))
			return curKeys[keycode] && !pasKeys[keycode];
		else
			return false;
	}

	bool Window::isKeyReleased(uint keycode)
	{
		if (keyExists(keycode))
			return !curKeys[keycode] && pasKeys[keycode];
		else
			return false;
	}

	bool Window::isKeyDown(uint keycode)
	{
		if (keyExists(keycode))
			return curKeys[keycode];
		else
			return false;
	}

	bool Window::mouseButtonExists(uint keycode)
	{
		if (keycode >= MAX_MOUSEBUTTONS)
		{
			LOG_WARNING("WINDOW", "Mouse button could not be found: ", keycode);
			return false;
		}
		return true;
	}

	bool Window::isMouseButtonPressed(uint button)
	{
		if (mouseButtonExists(button))
			return curMouseButtons[button] && !pasMouseButtons[button];
		else
			return false;
	}

	bool Window::isMouseButtonReleased(uint button)
	{
		if (mouseButtonExists(button))
			return !curMouseButtons[button] && pasMouseButtons[button];
		else
			return false;
	}

	bool Window::isMouseButtonDown(uint button)
	{
		if (mouseButtonExists(button))
			return curMouseButtons[button];
		else
			return false;
	}

	bool Window::closed()
	{
		return glfwWindowShouldClose(window) == 1;
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::tick()
	{
		checkJoysticks();
	}

	void Window::checkJoysticks()
	{
		for (int i = 0; i < MAX_JOYSTICKS; i++)
		{
			if (!joysticks[i].m_connected)
			{
				if (joysticks[i].checkConnect())
				{
					for (uint j = 0;j < joystickState.size();j++)
						joystickState[i]->joystickState(i, JOYSTICK_STATE_CONNECTED);
				}
			}
		}
	}

	void Window::update()
	{
		memcpy(pasKeys, curKeys, MAX_KEYS);
		memcpy(pasMouseButtons, curMouseButtons, MAX_MOUSEBUTTONS);
		if (focus){
			for (int i = 0; i < MAX_JOYSTICKS; i++)
			{
				if (joysticks[i].m_connected)
				{
					joysticks[i].update();
					if (joystickState.size()>0 && !joysticks[i].m_connected && joysticks[i].m_wasConnected)
					{
						for (uint j = 0;j < joystickState.size();j++)
							joystickState[j]->joystickState(j, JOYSTICK_STATE_DISCONNECTED);
					}
				}
			}
		}
	}

	void Window::render()
	{
		audio::SoundManager::update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Window::setBackgroundColor(math::vec4 color)
	{
		bgColor = color;
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Window::addResizeCallback(WindowResizeListener* listener)
	{
		windowResize.push_back(listener);
	}

	void Window::addWindowFocusCallback(WindowFocusListener* listener)
	{
		windowFocus.push_back(listener);
	}

	void Window::addJoystickCallback(JoystickStateListener* listener)
	{
		joystickState.push_back(listener);
	}

	void Window::window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window::width = width;
		Window::height = height;
		for (uint i = 0;i < Window::windowResize.size();i++)
			windowResize[i]->windowResize(width,height);
	}

	void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		curKeys[key] = action != GLFW_RELEASE;
	}

	void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
	{
		curMouseButtons[button] = action != GLFW_RELEASE;
	}

	void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePos = math::vec2(xpos / width, 1.0f-(ypos / height))*2.0f - 1.0f;
		mousePosPixel = math::vec2(xpos, ypos);
	}

	void Window::window_focus_callback(GLFWwindow* window,int state)
	{
		focus = state == GL_TRUE;
		for (uint i = 0;i < windowFocus.size();i++)
			windowFocus[i]->windowFocus(state);
		if (!focus){
			for (int i = 0; i < MAX_JOYSTICKS; i++)
			{
				joysticks[i].clearInput();
			}
		}
	}
}}
