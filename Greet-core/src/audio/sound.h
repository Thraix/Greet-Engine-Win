#pragma once

#include <string>
#include <logging/Log.h>
#include "AudioChannelManager.h"
#include "AudioChannel.h"

#include <ga.h>
#include <gau.h>

namespace Greet{

	class Sound
	{
	private:
		AudioChannel* m_channel;
		ga_Sound *m_sound;
		ga_Handle *m_handle;
		std::string m_name;
		bool m_playing;

	public:
		Sound(const std::string& filename, const std::string& name, std::string channelName);
		Sound(const std::string& filename, const std::string& name, AudioChannel* channel);
		~Sound();

		void play();
		void loop();
		void pause();
		void resume();
		void stop();
		void refreshChannel();

		inline const AudioChannel* getAudioChannel() const { return m_channel; }
		inline const std::string& getName() const { return m_name; }
		inline const bool isPlaying() const { return m_playing; }

		static void destroy_on_finish(ga_Handle* in_handle, void* in_context);
		static void loop_on_finish(ga_Handle* in_handle, void* in_context);
	};
}