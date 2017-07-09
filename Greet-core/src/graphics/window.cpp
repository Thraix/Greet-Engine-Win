#include "window.h"

namespace greet { namespace graphics {

	using namespace listener;

	std::vector<input::Joystick> Window::joysticks;
	bool Window::focus;
	math::vec2 Window::mousePos;
	math::vec2 Window::mousePosPixel;
	uint Window::width;
	uint Window::height;
	std::string Window::title;
	GLFWwindow *Window::window;
	math::vec4 Window::bgColor;
	bool Window::mouseButtonDown[MAX_MOUSEBUTTONS];
	bool Window::isMouseButtonDown;
	uint Window::joystickCheck;


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
		memset(mouseButtonDown,false,MAX_MOUSEBUTTONS);
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
		glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwMakeContextCurrent(window);

		//glfwSetWindowUserPointer(window,this);

		glfwSetFramebufferSizeCallback(window, window_resize);
		glfwSetKeyCallback(window,key_callback);
		glfwSetMouseButtonCallback(window,mouse_button_callback);
		glfwSetCursorPosCallback(window,mouse_position_callback);
		glfwSetWindowFocusCallback(window,window_focus_callback);
		glfwSetScrollCallback(window, mouse_scroll_callback);
		glfwSetCharCallback(window, key_char_callback);

		glfwSwapInterval(0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ASSERT(glewInit() == GLEW_OK,"Glew failed to init.");

		// SET DEFAULT VALUES
		FontManager::add(new FontContainer("Roboto-Black.ttf","roboto-bold"));
		FontManager::add(new FontContainer("Roboto-thin.ttf","roboto"));
		uint width,height,bpp;
		TextureManager::add(new Texture2D("frame.png","frame"));
		utils::UUID::init();

		LOG_INFO("WINDOW", "OpenGL Version: ", glGetString(GL_VERSION));
		LOG_INFO("WINDOW", "GLFW Version:   ", glfwGetVersionString());
		checkJoysticks();
		return true;
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
		if (joysticks[joystickCheck].checkConnect())
		{
			for (uint j = 0;j < joystickState.size();j++)
				joystickState[joystickCheck]->joystickState(joystickCheck, JOYSTICK_STATE_CONNECTED);
			joystickCheck++;
		}
	}

	void Window::update()
	{
		if (focus){
			for (int i = MAX_JOYSTICKS-1; i >= 0; i--)
			{
				if (joysticks[i].m_connected)
				{
					joysticks[i].update();
					if (joystickState.size()>0 && !joysticks[i].m_connected && joysticks[i].m_wasConnected)
					{
						for (uint j = 0;j < joystickState.size();j++)
							joystickState[j]->joystickState(j, JOYSTICK_STATE_DISCONNECTED);
						joystickCheck = i;
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

	void Window::removeResizeCallback(WindowResizeListener* listener)
	{

		windowResize.erase(std::remove(windowResize.begin(), windowResize.end(), listener));
	}

	void Window::addWindowFocusCallback(WindowFocusListener* listener)
	{
		windowFocus.push_back(listener);
	}

	void Window::removeWindowFocusCallback(WindowFocusListener* listener)
	{
		windowFocus.erase(std::remove(windowFocus.begin(), windowFocus.end(), listener));
	}

	void Window::addJoystickCallback(JoystickStateListener* listener)
	{
		joystickState.push_back(listener);
	}

	void Window::removeJoystickCallback(JoystickStateListener* listener)
	{
		joystickState.erase(std::remove(joystickState.begin(), joystickState.end(), listener));
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
		if (action == GLFW_RELEASE)
			event::EventDispatcher::onKeyReleased(event::KeyReleasedEvent(key));
		else if(action == GLFW_PRESS)
			event::EventDispatcher::onKeyPressed(event::KeyPressedEvent(key));
	}

	void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
	{
		mouseButtonDown[action] = action == GLFW_PRESS;
		if (action == GLFW_RELEASE)
			event::EventDispatcher::onMouseReleased(event::MouseReleasedEvent(mousePosPixel.x,mousePosPixel.y,button));
		else if (action == GLFW_PRESS)
			event::EventDispatcher::onMousePressed(event::MousePressedEvent(mousePosPixel.x, mousePosPixel.y, button));
		isMouseButtonDown = mouseButtonDown[action];
		if(!isMouseButtonDown)
			for (uint i = 0;i < MAX_MOUSEBUTTONS;i++)
				if (mouseButtonDown[i])
					isMouseButtonDown = true;

	}

	void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		event::EventDispatcher::onMouseMoved(event::MouseMovedEvent(xpos, ypos, xpos - mousePosPixel.x, ypos - mousePosPixel.y, isMouseButtonDown));
		mousePos = math::vec2(xpos / width, 1.0f - (ypos / height))*2.0f - 1.0f;
		mousePosPixel = math::vec2(xpos, ypos);
	}

	void Window::mouse_scroll_callback(GLFWwindow* window, double scrollX, double scrollY)
	{
		event::EventDispatcher::onMouseScrolled(event::MouseScrollEvent(scrollY));
	}

	void Window::key_char_callback(GLFWwindow* window, uint charCode)
	{
		event::EventDispatcher::onKeyTyped(event::KeyTypedEvent(charCode));
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
