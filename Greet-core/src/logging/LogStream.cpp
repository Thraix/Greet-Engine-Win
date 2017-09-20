#include "LogStream.h"
#include <iostream>
#include "Log.h"

LogStream::LogStream()
	: m_stream(std::cout), m_logLevel(LogLevel::information), m_name(""), m_levelCheck(*gteCheck)
{

}


LogStream::LogStream(std::ostream& stream, LogLevel logLevel, const std::string& name)
 : m_stream(stream), m_logLevel(logLevel), m_name(name), m_levelCheck(*gteCheck)
{

}

LogStream::LogStream(std::ostream& stream, LogLevel logLevel, const std::string& name, LevelCheck levelCheck)
	: m_stream(stream), m_logLevel(logLevel), m_name(name), m_levelCheck(levelCheck)
{

}

LogStream::~LogStream()
{
	
}

void LogStream::setLogLevel(LogLevel level)
{
	m_logLevel = level;
}

bool operator==(const LogStream& stream, const std::string& name)
{
	return !stream.m_name.compare(name);
}

bool operator!=(const LogStream& stream, const std::string& name)
{
	return stream.m_name.compare(name);
}

bool operator==(const LogStream& stream1, const LogStream& stream2)
{
	return !stream1.m_name.compare(stream2.m_name);
}

LogStream& LogStream::operator=(const LogStream& stream)
{
	std::cout << "no copyng cunt" << std::endl;
	ASSERT(false, "Cannot copy LogStream");
	return *this;
}

bool LogStream::eqCheck(const LogLevel& myLevel, const LogLevel& outputLevel)
{
	return myLevel == outputLevel;
}

bool LogStream::neqCheck(const LogLevel& myLevel, const LogLevel& outputLevel)
{
	return myLevel != outputLevel;
}

bool LogStream::gteCheck(const LogLevel& myLevel, const LogLevel& outputLevel)
{
	return myLevel >= outputLevel;
}

bool LogStream::gtCheck(const LogLevel& myLevel, const LogLevel& outputLevel)
{
	return myLevel > outputLevel;
}

bool LogStream::lteCheck(const LogLevel& myLevel, const LogLevel& outputLevel)
{
	return myLevel <= outputLevel;
}

bool LogStream::ltCheck(const LogLevel& outputLevel, const LogLevel& myLevel)
{
	return myLevel < outputLevel;
}
