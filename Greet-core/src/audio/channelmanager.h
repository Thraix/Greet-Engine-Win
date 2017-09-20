#pragma once

#include <vector>
#include <audio/channel.h>
#include <logging/log.h>
#include <internal/greet_types.h>
#include <utils/errorhandler.h>

namespace greet {
	namespace audio {
		class ChannelManager
		{
		private:
			static std::vector<audio::Channel*> m_channels;
		public:
			static void add(audio::Channel* channel);
			static audio::Channel* get(const std::string& channelname);
			static void destroy();
		private:
			ChannelManager(){}
		};
	}
}
