#include "window.h"

#include "guis/gui.h"

namespace greet { namespace graphics {
	using namespace listener;
	std::vector<input::Joystick> Window::m_joysticks;
	bool Window::m_curKeys[MAX_KEYS];
	bool Window::m_curMouseButtons[MAX_MOUSEBUTTONS];
	bool Window::m_pasKeys[MAX_KEYS];
	bool Window::m_pasMouseButtons[MAX_MOUSEBUTTONS];
	math::vec2 Window::m_mousePos;


	Window::Window(const char *title, int width, int height)
	{
		m_focus = true;
		m_title = title;
		m_width = width;
		m_height = height;

		managers::SoundManager::init();
		memset(m_curKeys, false, MAX_KEYS);
		memset(m_pasKeys, false, MAX_KEYS);
		memset(m_curMouseButtons, false, MAX_MOUSEBUTTONS);
		memset(m_curMouseButtons, false, MAX_MOUSEBUTTONS);

		for (int i = 0; i < MAX_JOYSTICKS; i++)
		{
			m_joysticks.push_back(input::Joystick(i, 0.3f, 0.3f));
		}

		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		managers::FontManager::destroy();
		managers::SoundManager::destroy();
		managers::ChannelManager::destroy();
		GUI::cleanUp();
		utils::UUID::cleanUp();
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			GREET_FATAL("WINDOW","Failed to initialize GLFW!");
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
		if (!m_window)
		{
			GREET_FATAL("WINDOW", "Failed to initialize GLFW!");
			return false;
		}
		//glfwSetInputMode(m_window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window,this);

		glfwSetFramebufferSizeCallback(m_window, window_resize);
		glfwSetKeyCallback(m_window,key_callback);
		glfwSetMouseButtonCallback(m_window,mouse_button_callback);
		glfwSetCursorPosCallback(m_window,mouse_position_callback);
		glfwSetWindowFocusCallback(m_window,window_focus_callback);

		glfwSwapInterval(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (glewInit() != GLEW_OK)
		{
			GREET_FATAL("WINDOW", "Failed to initialize GLFW!");
			return false;
		}

		// SET DEFAULT VALUES
		managers::FontManager::add(new Font("default", "default"));
		GUI::setDefaults(managers::FontManager::get("default"));
		utils::UUID::init();

		GREET_INFO("WINDOW", "OpenGL Version: ", glGetString(GL_VERSION));
		GREET_INFO("WINDOW", "GLFW Version:   ", glfwGetVersionString());

		return true;
	}

	bool Window::keyExists(uint keycode)
	{
		if (keycode >= MAX_KEYS)
		{
			GREET_WARN("WINDOW", "Key could not be found: ", keycode);
			return false;
		}
		return true;
	}

	bool Window::isKeyPressed(uint keycode)
	{
		if (keyExists(keycode))
			return m_curKeys[keycode] && !m_pasKeys[keycode];
		else
			return false;
	}

	bool Window::isKeyReleased(uint keycode)
	{
		if (keyExists(keycode))
			return !m_curKeys[keycode] && m_pasKeys[keycode];
		else
			return false;
	}

	bool Window::isKeyDown(uint keycode)
	{
		if (keyExists(keycode))
			return m_curKeys[keycode];
		else
			return false;
	}

	bool Window::mouseButtonExists(uint keycode)
	{
		if (keycode >= MAX_MOUSEBUTTONS)
		{
			GREET_WARN("WINDOW", "Mouse button could not be found: ", keycode);
			return false;
		}
		return true;
	}

	bool Window::isMouseButtonPressed(uint button)
	{
		if (mouseButtonExists(button))
			return m_curMouseButtons[button] && !m_pasMouseButtons[button];
		else
			return false;
	}

	bool Window::isMouseButtonReleased(uint button)
	{
		if (mouseButtonExists(button))
			return !m_curMouseButtons[button] && m_pasMouseButtons[button];
		else
			return false;
	}

	bool Window::isMouseButtonDown(uint button)
	{
		if (mouseButtonExists(button))
			return m_curMouseButtons[button];
		else
			return false;
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window) == 1;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::tick()
	{
		for (int i = 0; i < MAX_JOYSTICKS; i++)
			if (!m_joysticks[i].m_connected)
		{
			if (m_joysticks[i].checkConnect())
			{
				for (uint j = 0;j < f_joystickState.size();j++)
					f_joystickState[i]->joystickState(i, JOYSTICK_STATE_CONNECTED);
			}
		}
	}

	void Window::update()
	{
		memcpy(m_pasKeys, m_curKeys, MAX_KEYS);
		memcpy(m_pasMouseButtons, m_curMouseButtons, MAX_MOUSEBUTTONS);
		GUI::updateGUI();
		if (m_focus){
			for (int i = 0; i < MAX_JOYSTICKS; i++)
			{
				if (m_joysticks[i].m_connected)
				{
					m_joysticks[i].update();
					if (f_joystickState.size()>0&&!m_joysticks[i].m_connected&&m_joysticks[i].m_wasConnected)
					{
						for (uint j = 0;j < f_joystickState.size();j++)
							f_joystickState[j]->joystickState(j, JOYSTICK_STATE_DISCONNECTED);
					}
				}
			}
		}
	}

	void Window::render()
	{
		managers::SoundManager::update();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void Window::setBackgroundColor(math::vec4 color)
	{
		m_bgColor = color;
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Window::addResizeCallback(WindowResizeListener* listener)
	{
		f_windowResize.push_back(listener);
	}

	void Window::addWindowFocusCallback(WindowFocusListener* listener)
	{
		f_windowFocus.push_back(listener);
	}

	void Window::addJoystickCallback(JoystickStateListener* listener)
	{
		f_joystickState.push_back(listener);
	}

	void Window::window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_width = width;
		win->m_height = height;
		for (uint i = 0;i < win->f_windowResize.size();i++)
			win->f_windowResize[i]->windowResize(width,height);
	}

	void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		Window *win = (Window*) glfwGetWindowUserPointer(window);
		win->m_curKeys[key] = action != GLFW_RELEASE;
	}

	void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_curMouseButtons[button] = action != GLFW_RELEASE;
	}

	void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mousePos = math::vec2(xpos / win->getWidth(), 1.0f-(ypos / win->getHeight()))*2.0f - 1.0f;
	}

	void Window::window_focus_callback(GLFWwindow* window,int state)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_focus = state == GL_TRUE;
		for (uint i = 0;i < win->f_windowFocus.size();i++)
			win->f_windowFocus[i]->windowFocus(state);
		if (!win->m_focus){
			for (int i = 0; i < MAX_JOYSTICKS; i++)
			{
				win->m_joysticks[i].clearInput();
			}
		}
	}
}}