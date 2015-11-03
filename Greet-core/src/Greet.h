#pragma once

#include <graphics/window.h>
#include <utils/timer.h>

namespace greet{

	class Greet
	{
	protected:
		graphics::Window* m_window;
		utils::Timer* m_timer;
		uint m_fps;
		uint m_ups;
	protected:
		Greet()
			: m_fps(0), m_ups(0)
		{
		}

		virtual ~Greet()
		{
			delete m_timer;
			delete m_window;
		}

		void createWindow(const char* title, int width, int height)
		{
			m_window = new graphics::Window(title, width, height);
			graphics::Window::setUserPointer(m_window,this);
			graphics::Window::setResizeCallback(m_window, &resize_callback);
			graphics::Window::setJoystickCallback(m_window, &joystick_state_callback);
			graphics::Window::setWindowFocusCallback(m_window, &window_focus_callback);
		}


		virtual void init() = 0;
		virtual void tick() = 0;
		virtual void update(float elapsedTime) = 0;
		virtual void render() = 0;
		virtual void resize(int width, int height){}
		virtual void joystickConnect(uint joystick, bool connect){}
		virtual void windowFocus(bool focused) {}

		const uint getFPS() const { return m_fps; }
		const uint getUPS() const { return m_fps; }

		static void resize_callback(graphics::Window* window, int width, int height)
		{
			Greet* greet = (Greet*)graphics::Window::getUserPointer(window);
			greet->resize(width,height);
		}

		static void joystick_state_callback(graphics::Window* window, uint joystick, unsigned char state)
		{
			Greet* greet = (Greet*)graphics::Window::getUserPointer(window);
			greet->joystickConnect(joystick, state == JOYSTICK_STATE_CONNECTED);
		}

		static void window_focus_callback(graphics::Window* window, int state)
		{
			Greet* greet = (Greet*)graphics::Window::getUserPointer(window);
			greet->windowFocus(state==GL_TRUE);
		}

	public:
		void start()
		{
			init();
			run();
		}

	private:
		void run()
		{
			m_timer = new utils::Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			uint frames = 0;
			uint updates = 0;

			int lastWidth = m_window->getWidth();
			int lastHeight = m_window->getHeight();

			while (!m_window->closed())
			{
				m_window->clear();
				float elapsed = m_timer->elapsed();
				if (elapsed - updateTimer >= updateTick)
				{
					update(updateTick);
					m_window->update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_window->render();

				if (elapsed - timer >= 1.0f)
				{
					m_fps = frames;
					m_ups = updates;
					m_window->tick();
					tick();
					frames = 0;
					updates = 0;
					timer += 1.0f;
				}
			}
		}
	};
}