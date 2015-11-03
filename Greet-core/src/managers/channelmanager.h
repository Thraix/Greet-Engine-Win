#pragma once

#include <vector>
#include <audio/channel.h>
#include <utils/log.h>
#include <greet_types.h>
namespace greet {
	namespace managers {
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