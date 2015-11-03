#include "channelmanager.h"

namespace greet{ namespace managers {

		std::vector<audio::Channel*> ChannelManager::m_channels;

		void ChannelManager::add(audio::Channel* sound)
		{
			m_channels.push_back(sound);
		}

		audio::Channel* ChannelManager::get(const std::string& soundname)
		{
			uint size = m_channels.size();

			for (uint i = 0; i < size; i++)
				if (soundname.compare(m_channels[i]->getName()) == 0)
					return m_channels[i];
			GREET_ERROR("CHANNELMANAGER", "Could not find the given channel: ", soundname.c_str());
			return m_channels[0];
		}

		void ChannelManager::destroy()
		{
			for (uint i = 0; i < m_channels.size(); i++)
				delete m_channels[i];
		}

	}
}