#pragma once

#include <vector>
#include <audio/sound.h>
#include <greet_types.h>

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace greet { namespace managers {
	class SoundManager
	{
	private:
		friend class audio::Sound;
		static gau_Manager* m_manager;
		static ga_Mixer* m_mixer;
		static std::vector<audio::Sound*> m_sounds;
	public:
		static void init();
		static void add(audio::Sound* sound);
		static audio::Sound* get(const std::string& soundname);
		static void destroy();
		static void update();
	private:
		SoundManager(){}
	};
}}