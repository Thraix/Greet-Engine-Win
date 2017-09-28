#pragma once
#include <iostream>

#include "LogLevel.h"
#include "LogStream.h"

#include <vector>
namespace Greet {
	class Logger
	{
	private:
		std::vector<LogStream*> m_streams;	
	public:
		Logger();
		virtual ~Logger();

		/*
		Logs the given type to all the LogStream's if they allow the given LogLevel.
		*/
		template <typename... Args>
		void log(const LogLevel& level, const Args&... args)
		{ 
			for (std::vector<LogStream*>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
			{
				(*it)->output(level,args...);
			}
		}
		void addLogStream(LogStream* stream);
		LogStream* getLogStream(const std::string& name);
		LogStream* removeLogStream(const std::string& name);
		LogStream* removeLogStream(LogStream* stream);
	};
}