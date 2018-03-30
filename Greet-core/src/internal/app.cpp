#include "app.h"
#include <drivers/DriverDispatcher.h>
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
		Window::DestroyWindow();
	}

	void App::CreateWindow(std::string title, int width, int height)
	{
		Window::CreateWindow(title, width, height);
		Window::AddResizeCallback(this);
		Window::AddJoystickCallback(this);
		Window::AddWindowFocusCallback(this);
		m_initialized = true;
	}

	void App::Start()
	{
		Init();
		Run();
	}

	void App::Run()
	{
		if (!m_initialized)
		{
			Log::Error("Window is not initalized, set it in App::createWindow");
			return;
		}
		m_timer = new Timer();
		double timer = 0.0f;
		double updateTimer = 0.0f;
		double updateTick = 1.0 / 300.0;
		double renderTimer = 0.0f;

		uint frames = 0;
		uint updates = 0;

		while (!Window::Closed())
		{
			double elapsed = m_timer->Elapsed();
			if (elapsed - updateTimer >= updateTick)
			{
				DriverDispatcher::Update(updateTick);
				Window::Update();
				RenderEngine::Update(elapsed - updateTimer);
				Update(elapsed - updateTimer);
				updates++;
				updateTimer = elapsed;
			}
			if (elapsed - renderTimer >= frameCap)
			{
				Window::Clear();
				Render();
				RenderEngine::Render();
				Window::Render();
				frames++;
				renderTimer = elapsed;
			}

			if (elapsed - timer >= 1.0)
			{
				m_fps = frames;
				m_ups = updates;
				Window::Tick();
				Tick();
				frames = 0;
				updates = 0;
				timer += 1.0;
			}
			elapsed = m_timer->Elapsed();
			double timeToNext = fmin(frameCap - (elapsed - renderTimer),updateTick - (elapsed-updateTimer))*1000*0.5;
			if (timeToNext >= 1)
				std::this_thread::sleep_for(std::chrono::milliseconds((long long)timeToNext));
		}
	}
}
