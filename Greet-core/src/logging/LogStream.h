#pragma once

#include "LogLevel.h"
#include <ostream>

typedef bool(*LevelCheck)(const LogLevel& myLevel, const LogLevel& outputLevel);

class LogStream
{
	friend class Logger;
private:
	/* Outputstream for the LogStream */
	std::ostream& m_stream;
	/* Loglevel that is compared with the given log level whilst outputing */
	LogLevel m_logLevel;
	/* The comparison that checks if the stream should output this with a given LogLevel*/
	LevelCheck m_levelCheck;
	/* Name of the LogStream, used to differantiate streams */
	std::string m_name;
private:
	LogStream();
public:

	LogStream(std::ostream& stream, LogLevel logLevel, const std::string& name);
	LogStream(std::ostream& stream, LogLevel logLevel, const std::string& name, LevelCheck levelCheck);
	virtual ~LogStream();

	/*
		Output the given arguments to the stream with a given LogLevel
	*/
	template<typename... Args>
	void output(const LogLevel& level, const Args&... args)
	{
		// Check if the given level is allowed to be streamed.
		if (m_levelCheck(m_logLevel, level))
		{
			// Output all the arguments with an endline
			put("[GREET]", args..., '\n');
		}
	}


	/*
		return the name of the stream.
	*/
	const std::string& getName() const { return m_name; }

	/* 
		Set the loglevel for the stream
	*/
	void setLogLevel(LogLevel level);

	/*
	Checks if the stream name is equal to the given name parameter
	*/
	friend bool operator==(const LogStream& stream, const std::string& name);

	/*
	Checks if the stream name is equal to the given name parameter
	*/
	friend bool operator!=(const LogStream& stream, const std::string& name);

	/*
	Checks if the stream name is equal to the given streams name
	*/
	friend bool operator==(const LogStream& stream1, const LogStream& stream2);

	/*
		for some reason this is needed.
	*/
	LogStream& operator=(const LogStream& stream);

	// Default level checks, returns true if the given stream should stream with the given output level.
	static bool eqCheck(const LogLevel& myLevel, const LogLevel& outputLevel);
	static bool neqCheck(const LogLevel& myLevel, const LogLevel& outputLevel);
	static bool gteCheck(const LogLevel& myLevel, const LogLevel& outputLevel);
	static bool gtCheck(const LogLevel& myLevel, const LogLevel& outputLevel);
	static bool lteCheck(const LogLevel& myLevel, const LogLevel& outputLevel);
	static bool ltCheck(const LogLevel& myLevel, const LogLevel& outputLevel);

private:

	/*
		Put all the arguments to the stream.
	*/
	template<typename T, typename... Args>
	void put(const T& t, const Args&... args)
	{
		// Put one argument to the stream.
		put(t);
		// Put the rest of the arguments to the stream (if only one, put(const T&) is called)
		put(args...);
	}

	/*
		Put the arguments to the stream.
	*/
	template <typename T>
	void put(const T& t)
	{
		m_stream << t;
	}

};