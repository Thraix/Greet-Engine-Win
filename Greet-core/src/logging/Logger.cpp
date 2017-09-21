#include "logger.h"
#include "Log.h"
namespace Greet {

	LogStream Logger::invalid;

	Logger::Logger()
	{
	
	}

	Logger::~Logger()
	{
		m_streams.clear();
	}

	void Logger::addLogStream(const LogStream& stream)
	{
		// Check if there already is a stream with the given stream name. (getLogStream returns a stream with an empty name if none is found)
		if (getLogStream(stream.getName()) != "")
		{
			Log::error("Stream with name ", stream.getName(), " already exists.");
		}
		else
			m_streams.push_back(stream);
	}

	const LogStream& Logger::getLogStream(const std::string& name)
	{
		for (std::vector<LogStream>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
		{
			// it -> pointer to pointer to stream
			if (*it == name)
			{
				return *it;
			}
		}
		return invalid;
	}

	LogStream Logger::removeLogStream(const std::string& name)
	{
		for (std::vector<LogStream>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
		{
			if (*it == name)
			{
				LogStream& s = *it;
				m_streams.erase(it);
				return s;
			}
		}
		Log::warning("No stream removed with name: ", name, ". Could not find.");
	}

	LogStream Logger::removeLogStream(LogStream stream)
	{
		return removeLogStream(stream.getName());
	}

}