#pragma once

#include <graphics/window.h>
#include <utils/timer.h>
#include <logging/logger.h>
#include <graphics/renderengine.h>

namespace greet { namespace internal {


	class App : public listener::WindowListener, public listener::JoystickStateListener
	{
	protected:
		utils::Timer* m_timer;
		uint m_fps;
		uint m_ups;
		double frameCap = 0;
		bool m_initialized = false;
	protected:
		App();

		virtual ~App();

		void createWindow(std::string title, int width, int height);


		virtual void init() = 0;
		virtual void tick() = 0;
		virtual void update(float elapsedTime) = 0;
		virtual void render() = 0;
		virtual void windowResize(int width, int height){}
		virtual void joystickState(uint joystick, bool connect){}
		virtual void windowFocus(bool focused) {}

		void setFrameCap(uint frameCap)
		{
			if (frameCap == 0)
				this->frameCap = 0;
			else
				this->frameCap = 1.0 / (double)frameCap;
		}

		uint getFrameCap()
		{
			if (frameCap == 0)
				return 0;
			return (uint)(1.0 / frameCap);
		}

		const uint getFPS() const { return m_fps; }
		const uint getUPS() const { return m_fps; }

	public:
		void start();

	private:
		void run();
	};
}}
