#include "app.h"
#include <drivers/driverdispatcher.h>
#include <chrono>
#include <thread>
namespace Greet {

	App::App()
	: m_fps(0), m_ups(0)
	{
		//std::ofstream file(".logging");
		//LogStream* fileStream = new LogStream(file, LogLevel::error, "fileStream");
		//Log::addLogStream(fileStream);
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

	void App::run()
	{
		if (!m_initialized)
		{
			Log::error("Window is not initalized, set it in App::createWindow");
			return;
		}
		m_timer = new Timer();
		double timer = 0.0f;
		double updateTimer = 0.0f;
		double updateTick = 1.0 / 300.0;
		double renderTimer = 0.0f;

		uint frames = 0;
		uint updates = 0;

		while (!Window::closed())
		{
			double elapsed = m_timer->elapsed();
			if (elapsed - updateTimer >= updateTick)
			{
				DriverDispatcher::update(updateTick);
				update(elapsed - updateTimer);
				Window::update();
				RenderEngine::update(elapsed - updateTimer);
				updates++;
				updateTimer = elapsed;
			}
			if (elapsed - renderTimer >= frameCap)
			{
				Window::clear();
				render();
				RenderEngine::render();
				Window::render();
				frames++;
				renderTimer = elapsed;
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
			elapsed = m_timer->elapsed();
			double timeToNext = fmin(frameCap - (elapsed - renderTimer),updateTick - (elapsed-updateTimer))*1000*0.5;
			if (timeToNext >= 1)
				std::this_thread::sleep_for(std::chrono::milliseconds((long long)timeToNext));
		}
	}
}
