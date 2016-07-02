#pragma once
#include <chrono>
namespace greet { namespace utils{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::system_clock> m_start;
		std::chrono::time_point<std::chrono::system_clock> m_end;
		double m_frequency;
	public:
		Timer()
		{
			m_start = std::chrono::system_clock::now();
		}

		void reset()
		{
			m_start = std::chrono::system_clock::now();
		}

		double elapsed()
		{	
			m_end = std::chrono::system_clock::now();		
			std::chrono::duration<double> elapsed = m_end - m_start;
			return elapsed.count();
		}
	};
}}