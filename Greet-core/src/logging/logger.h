#pragma once

#include <string.h>
#include <fstream>
#include <iostream>
#include "loggable.h"
#include <utils/logutils.h>

#define LOG_BUFFER_SIZE 1024*10

#define LOG_LEVEL_QUIET		0
#define LOG_LEVEL_FATAL 	1
#define LOG_LEVEL_ERROR 	2
#define LOG_LEVEL_WARNING  	3
#define LOG_LEVEL_INFO  	4
#define LOG_LEVEL_DEBUG  	4

#ifndef LOG_LEVEL_FILE
	#define LOG_LEVEL_FILE LOG_LEVEL_ERROR
#endif

#ifndef LOG_LEVEL_PRINT
	#define LOG_LEVEL_PRINT LOG_LEVEL_INFO
#endif

#if LOG_LEVEL_FILE > LOG_LEVEL_PRINT
	#define LOG_LEVEL LOG_LEVEL_FILE
#else
	#define LOG_LEVEL LOG_LEVEL_PRINT
#endif

namespace greet { namespace logging
{
	typedef void(*LOG_FLUSH)();
	
	static int consolePosition = 0;
	static int lastConsolePosition = 0;
	static int filePosition = 0;
	static int lastFilePosition = 0;
	static char buffer[LOG_BUFFER_SIZE+1];
	static char fileBuffer[LOG_BUFFER_SIZE+1];

	inline void flushToFile()
	{
		std::ofstream outfile;
		outfile.open("logs/.log",std::ios_base::app);
		outfile << &fileBuffer[lastFilePosition];
		lastFilePosition = filePosition;
	}
	
	inline void flushToConsole()
	{
		std::cout << &buffer[lastConsolePosition];
		lastConsolePosition = consolePosition;
	}
	
	inline void append(int logLevel, int maxLevel, const char* str, char* buffer, int& position, int& lastPosition, LOG_FLUSH flush)
	{
		size_t len = strlen(str);
		if(logLevel <= maxLevel)
		{
			int offset = 0;
			while(position+len>LOG_BUFFER_SIZE)
			{
				int len1 = len;
				if(LOG_BUFFER_SIZE-position < len)
					len1 = LOG_BUFFER_SIZE-position;
				strncpy(&buffer[position],&str[offset],len1);
				flush();
				memset(buffer,0,LOG_BUFFER_SIZE);
				position = 0;
				lastPosition = 0;
				offset += len1;
				len -= len1;
			}
			strncpy(&buffer[position],&str[offset],len);
			position += len;

		}
	}
	
	inline void append_buffer(int logLevel, const char* str)
	{
		append(logLevel,LOG_LEVEL_PRINT,str,buffer,consolePosition,lastConsolePosition,&flushToConsole);
		append(logLevel,LOG_LEVEL_FILE,str,fileBuffer,filePosition,lastFilePosition,&flushToFile);		
	}

	template <typename T>
	typename std::enable_if<std::is_base_of<const Loggable, T>::value>::type
	to_string(int logLevel, const T t)
	{
		append_buffer(logLevel, t.toString().c_str());
	}

	template <typename T>
	typename std::enable_if<!std::is_base_of<const Loggable, T>::value>::type
	to_string(int logLevel, const T t)
	{
		append_buffer(logLevel, utils::toString(t).c_str());
	}

	template <typename First>
	inline void log(bool newline, int logLevel, const First first)
	{
		to_string(logLevel,first);
		if(newline)
			append_buffer(logLevel,"\n");
		if(logLevel <= LOG_LEVEL_PRINT)
			flushToConsole();
		if(logLevel <= LOG_LEVEL_FILE)
			flushToFile();
		
	}
	
	template <typename First, typename... Args>
	inline void log(bool newline, int logLevel, const First first, Args... args)
	{
		to_string(logLevel,first);
		if(sizeof...(args))
		{
			append_buffer(logLevel," ");
			log(newline,logLevel,std::forward<Args>(args)...);
		}
	}
}}

#ifdef DEBUG
	#define LOG_DEBUG(...) greet::logging::log(true,LOG_LEVEL_DEBUG,"[GREET][DBG]:",__VA_ARGS__);}
#else
	#define LOG_DEBUG(...)
#endif

#define LOG_CLEAN(...) greet::logging::log(true,LOG_LEVEL_QUIET,__VA_ARGS__)

#if LOG_LEVEL >= LOG_LEVEL_INFO
	#define LOG_INFO(...) greet::logging::log(true,LOG_LEVEL_INFO,"[GREET][INF]:",__VA_ARGS__);
#else
	#define LOG_INFO(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
	#define LOG_WARNING(...) greet::logging::log(true,LOG_LEVEL_WARNING,"[GREET][WRN]:",__VA_ARGS__)
#else
	#define LOG_WARNING(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
	#define LOG_ERROR(...) greet::logging::log(true,LOG_LEVEL_ERROR,"[GREET][ERR]:",__VA_ARGS__)
#else
	#define LOG_ERROR(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_FATAL
	#define LOG_FATAL(...) greet::logging::log(true,LOG_LEVEL_FATAL,"[GREET][FTL]:",__VA_ARGS__)
#else
	#define LOG_FATAL(...)
#endif

#define ASSERT(x, ...) \
	do { \
	if (!(x)) \
			{ \
		LOG_CLEAN(""); \
		LOG_FATAL("*************************"); \
		LOG_FATAL("    ASSERTION FAILED!    "); \
		LOG_FATAL("Condition:", #x); \
		LOG_FATAL("Comment:",__VA_ARGS__); \
		LOG_FATAL(__FILE__,":", __LINE__); \
		LOG_FATAL("*************************"); \
		LOG_FLUSH_FILE; \
		*((unsigned int*)0) = 0xDEAD; \
			} \
		} while(0)

#define LOG_FLUSH_FILE greet::logging::flushToFile()
