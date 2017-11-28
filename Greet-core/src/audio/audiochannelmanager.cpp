#include "AudioChannelManager.h"

namespace Greet{

	std::vector<AudioChannel*> AudioChannelManager::m_channels;

	void AudioChannelManager::add(AudioChannel* channel)
	{
		for (int i = 0;i < m_channels.size();i++)
		{
			if (channel->getName() == m_channels[i]->getName())
			{
				ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
				Log::error("Given channel name already exists: ", channel->getName().c_str());
				return;
			}
		}
		m_channels.push_back(channel);
	}

	AudioChannel* AudioChannelManager::get(const std::string& channelname)
	{
		uint size = m_channels.size();

		for (uint i = 0; i < size; i++)
			if (channelname.compare(m_channels[i]->getName().c_str()) == 0)
				return m_channels[i];
		ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
		Log::error("Could not find the given channel: ", channelname.c_str());
		return m_channels[0];
	}

	void AudioChannelManager::destroy()
	{
		for (uint i = 0; i < m_channels.size(); i++)
			delete m_channels[i];
	}

}