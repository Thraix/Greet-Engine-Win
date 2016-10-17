#pragma once
#include <chrono>
namespace greet { namespace utils{
	class Timer
	{
	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	public:
		Timer()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		void reset()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		float elapsed()
		{	
			return std::chrono::duration_cast<std::chrono::duration<float,std::milli>>(std::chrono::high_resolution_clock::now() - m_start).count() / 1000.0f;
		}
	};
}}