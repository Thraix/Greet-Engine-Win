#pragma once

#include <vector>
#include <audio/Sound.h>
#include <internal/GreetTypes.h>
#include <utils/ErrorHandler.h>

#include <ga.h>
#include <gau.h>

namespace Greet {
	class SoundManager
	{
	private:
		friend class Sound;
		static gau_Manager* m_manager;
		static ga_Mixer* m_mixer;
		static std::vector<Sound*> m_sounds;
	public:
		static void init();
		static void add(Sound* sound);
		static Sound* get(const std::string& soundname);
		static void destroy();
		static void update();
	private:
		SoundManager(){}
	};
}
