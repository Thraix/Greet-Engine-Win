#pragma once

#include <graphics/window.h>
#include <utils/timer.h>
#include <listeners\listeners.h>

namespace greet{


	class Greet : public listener::WindowListener, public listener::JoystickStateListener
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
			m_window->addResizeCallback(this);
			m_window->addJoystickCallback(this);
			m_window->addWindowFocusCallback(this);
		}


		virtual void init() = 0;
		virtual void tick() = 0;
		virtual void update(float elapsedTime) = 0;
		virtual void render() = 0;
		virtual void windowResize(int width, int height){}
		virtual void joystickState(uint joystick, bool connect){}
		virtual void windowFocus(bool focused) {}

		const uint getFPS() const { return m_fps; }
		const uint getUPS() const { return m_fps; }

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