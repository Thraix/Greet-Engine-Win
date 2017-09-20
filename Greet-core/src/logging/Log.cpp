#include "Log.h"

Log Log::m_log;

Log::Log()
{
	m_logger.addLogStream(LogStream(std::cout, LogLevel::information, "console"));
}

Log::~Log()
{
	
}

void Log::addLogStream(LogStream stream)
{
	m_log.m_logger.addLogStream(stream);
}

LogStream& Log::removeLogStream(const std::string& name)
{
	return m_log.m_logger.removeLogStream(name);
}

LogStream& Log::removeLogStream(LogStream stream)
{
	return m_log.m_logger.removeLogStream(stream);
}