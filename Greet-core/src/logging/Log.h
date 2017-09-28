#pragma once

#include "Logger.h"
#include "LogLevel.h"

#define ASSERT(x,...) if(!(x)) {Greet::Log::error(__VA_ARGS__);abort();}

namespace Greet {
	/*
		Singleton class for logging
	*/
	class Log
	{
	private:
		// Logger for the logging system
		Logger m_logger;

		// Singleton Log
		static Log m_log;
	public:

	private:
		Log();
		virtual ~Log();
	public:

		/*
			Add a log stream to the logging system.
		*/
		static void addLogStream(LogStream stream);

		/*
		Remove a log stream from the logging system.
		*/
		static LogStream& removeLogStream(const std::string& name);

		/*
			Remove a log stream from the logging system.
		*/
		static LogStream& removeLogStream(LogStream stream);

		// Default logging capabilities

		/*
			Logging at information log level.
		*/
		template <typename... Args>
		static void info(const Args&... args)
		{
			m_log.m_logger.log(LogLevel::information, "[INF] ", args...);
		}

		/*
			Logging at warning log level.
		*/
		template <typename... Args>
		static void warning(const Args&... args)
		{
			m_log.m_logger.log(LogLevel::warning, "[WRN] ", args...);
		}

		/*
			Logging at error log level.
		*/
		template <typename... Args>
		static void error(const Args&... args)
		{
			m_log.m_logger.log(LogLevel::error,"[ERR] ",args...);
		}

		/*
			Logging at user defined log level.
		*/
		template <typename... Args>
		static void log(const LogLevel& level, const Args&... args)
		{
			m_log.m_logger.log(level, args...);
		}

	};
}