#pragma once

#include <vector>
#include <audio/AudioChannel.h>
#include <logging/Log.h>
#include <internal/GreetTypes.h>
#include <utils/ErrorHandler.h>

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
