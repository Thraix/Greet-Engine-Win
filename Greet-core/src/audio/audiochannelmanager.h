#pragma once

#include <vector>
#include <audio/audiochannel.h>
#include <logging/log.h>
#include <internal/Greet_types.h>
#include <utils/errorhandler.h>

namespace Greet {
	class AudioChannelManager
	{
	private:
		static std::vector<AudioChannel*> m_channels;
	public:
		static void add(AudioChannel* channel);
		static AudioChannel* get(const std::string& channelname);
		static void destroy();
	private:
		AudioChannelManager(){}
	};
}
