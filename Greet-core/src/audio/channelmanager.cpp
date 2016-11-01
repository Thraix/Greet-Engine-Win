#include "channelmanager.h"

namespace greet{ namespace audio {

		std::vector<audio::Channel*> ChannelManager::m_channels;

		void ChannelManager::add(audio::Channel* channel)
		{
			for (int i = 0;i < m_channels.size();i++)
			{
				if (channel->getName() == m_channels[i]->getName())
				{
					utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_ADD);
					LOG_ERROR("ATLASMANAGER", "Given atlas name already exists:", channel->getName().c_str());
					return;
				}
			}
			m_channels.push_back(channel);
		}

		audio::Channel* ChannelManager::get(const std::string& channelname)
		{
			uint size = m_channels.size();

			for (uint i = 0; i < size; i++)
				if (channelname.compare(m_channels[i]->getName().c_str()) == 0)
					return m_channels[i];
			utils::ErrorHandle::setErrorCode(GREET_ERROR_MANAGER_GET);
			LOG_ERROR("CHANNELMANAGER", "Could not find the given channel: ", channelname.c_str());
			return m_channels[0];
		}

		void ChannelManager::destroy()
		{
			for (uint i = 0; i < m_channels.size(); i++)
				delete m_channels[i];
		}

	}
}