#pragma once

#include <string.h>
#include <fstream>
#include <iostream>
#include "loggable.h"
#include <utils/logutils.h>
#include <utils/dialogbox.h>
#include <cstdlib>

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
	static int resetBufferPosition = 0;
	static int lastResetBufferPosition = 0;

	static char buffer[LOG_BUFFER_SIZE+1];
	static char fileBuffer[LOG_BUFFER_SIZE+1];
	static char resetBuffer[LOG_BUFFER_SIZE + 1];


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

	inline void flushNothing() {}
	
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
	to_buffer(int logLevel, const T t)
	{
		append_buffer(logLevel, t.toString().c_str());
	}

	template <typename T>
	typename std::enable_if<!std::is_base_of<const Loggable, T>::value>::type
	to_buffer(int logLevel, const T t)
	{
		append_buffer(logLevel, utils::toString(t).c_str());
	}

	template <typename T>
	typename std::enable_if<std::is_base_of<const Loggable, T>::value>::type
		to_buffer(const T t, char* buffer, int& position, int& lastPosition)
	{
		append(0,0,t.to_string(),buffer, position, lastPosition,&flushNothing);
	}

	template <typename T>
	typename std::enable_if<!std::is_base_of<const Loggable, T>::value>::type
		to_buffer(const T t, char* buffer, int& position, int& lastPosition)
	{
		append(0,0, utils::toString(t).c_str(),buffer,position, lastPosition,&flushNothing);
	}

	template <typename First>
	inline void log(bool newline, int logLevel, const First first)
	{
		to_buffer(logLevel,first);
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
		to_buffer(logLevel,first);
		if(sizeof...(args))
		{
			append_buffer(logLevel," ");
			log(newline,logLevel,std::forward<Args>(args)...);
		}
	}

	template <typename First>
	inline void resetBufferLog(bool newline, const First first)
	{
		to_buffer(first, resetBuffer, resetBufferPosition, lastResetBufferPosition);
		if (newline)
			to_buffer("\n", resetBuffer, resetBufferPosition, lastResetBufferPosition);
		resetBuffer[resetBufferPosition] = '\0';
		lastResetBufferPosition = resetBufferPosition;
		resetBufferPosition = 0;
	}

	template <typename First, typename... Args>
	inline void resetBufferLog(bool newline, const First first, Args... args)
	{
		to_buffer(first, resetBuffer, resetBufferPosition, lastResetBufferPosition);
		if (sizeof...(args))
		{
			to_buffer(" ", resetBuffer, resetBufferPosition, lastResetBufferPosition);
			resetBufferLog(newline, std::forward<Args>(args)...);
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
			greet::logging::resetBufferLog(false,"ASSERTION FAILED!\nCondition: "#x"\nComment:",__VA_ARGS__,"\n",__FILE__,":",__LINE__); \
			greet::utils::DialogBox::show(greet::logging::resetBuffer, "ASSERTION FAILED",greet::utils::DialogBox::Style::Error);\
			std::exit(EXIT_FAILURE); \
			} \
		} while(0)

#define LOG_FLUSH_FILE greet::logging::flushToFile()
/*			LOG_CLEAN(""); \
			LOG_FATAL("*************************"); \
			LOG_FATAL("    ASSERTION FAILED!    "); \
			LOG_FATAL("Condition:", #x); \
			LOG_FATAL("Comment:",__VA_ARGS__); \
			LOG_FATAL(__FILE__,":", __LINE__); \
			LOG_FATAL("*************************"); \
			LOG_INFO("" #x) \
			LOG_FLUSH_FILE; \ */
//		utils::DialogBox::show("*************************\n    ASSERTION FAILED!    \nCondition: "+std::to_string(#x)+"\nComment: " + std::to_string(__VA_ARGS__) + "\n" + std::to_string(__FILE__)+" : " + std::to_string(__LINE__) + "\n*************************",DialogBox::Style::Error); \
