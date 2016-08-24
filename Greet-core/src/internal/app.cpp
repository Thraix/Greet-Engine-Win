#include "app.h"
#include <chrono>
#include <thread>
#include <drivers/driverdispatcher.h>

namespace greet { namespace internal {
	using namespace graphics;
	App::App()
	: m_fps(0), m_ups(0)
	{

	}

	App::~App()
	{
		delete m_timer;
		Window::destroyWindow();
	}

	void App::createWindow(std::string title, int width, int height)
	{
		Window::createWindow(title, width, height);
		Window::addResizeCallback(this);
		Window::addJoystickCallback(this);
		Window::addWindowFocusCallback(this);
		m_initialized = true;
	}

	void App::start()
	{
		init();
		run();
	}

	void sleep(int x)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(x));
	}


	void App::run()
	{
		if (!m_initialized)
		{
			LOG_FATAL("Window is not initalized, set it in App::createWindow");
			return;
		}
		m_timer = new utils::Timer();
		double timer = 0.0f;
		double updateTimer = 0.0f;
		double updateTick = 1.0 / 60.0;
		double renderTimer = 0.0f;

		uint frames = 0;
		uint updates = 0;

		bool rendered = false;
		while (!Window::closed())
		{
			rendered = false;
			Window::clear();
			double elapsed = m_timer->elapsed();
			if (elapsed - updateTimer >= updateTick)
			{
				drivers::DriverDispatcher::update(updateTick);
				update(elapsed - updateTimer);
				Window::update();
				updates++;
				updateTimer += elapsed - updateTimer;
			}
			if (elapsed - renderTimer >= frameCap)
			{
				render();
				Window::render();
				frames++;
				renderTimer += frameCap;
				rendered = true;
			}

			if (elapsed - timer >= 1.0)
			{
				m_fps = frames;
				m_ups = updates;
				Window::tick();
				tick();
				frames = 0;
				updates = 0;
				timer += 1.0;
			}
			if(!rendered)
				sleep(1);
		}
	}

}}
