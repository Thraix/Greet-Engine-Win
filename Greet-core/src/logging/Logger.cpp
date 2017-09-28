#include "logger.h"
#include "Log.h"
namespace Greet {

	Logger::Logger()
	{
	
	}

	Logger::~Logger()
	{
		for (std::vector<LogStream*>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
		{
			delete *it;
		}
		m_streams.clear();
	}

	void Logger::addLogStream(LogStream* stream)
	{
		// Check if there already is a stream with the given stream name.
		if (getLogStream(stream->getName()))
		{
			Log::error("Stream with name ", stream->getName(), " already exists.");
		}
		else
			m_streams.push_back(stream);
	}

	LogStream* Logger::getLogStream(const std::string& name)
	{
		for (std::vector<LogStream*>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
		{
			// it -> pointer to pointer to stream
			if (**it == name)
			{
				return *it;
			}
		}
		return NULL;
	}

	LogStream* Logger::removeLogStream(const std::string& name)
	{
		for (std::vector<LogStream*>::iterator it = m_streams.begin(); it != m_streams.end(); it++)
		{
			if (**it == name)
			{
				m_streams.erase(it);
				return *it;
			}
		}
		Log::warning("No stream removed with name: ", name, ". Could not find.");
	}

	LogStream* Logger::removeLogStream(LogStream* stream)
	{
		return removeLogStream(stream->getName());
	}

}