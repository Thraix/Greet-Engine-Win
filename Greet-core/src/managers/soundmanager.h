#pragma once

#include <managers\manager.h>
#include <vector>
#include <internal/greet_types.h>
#include <audio/sound.h>

#include <ga.h>
#include <gau.h>

namespace greet { namespace managers {
	class SoundManager : public Manager<audio::Sound>
	{
	private:
		gau_Manager* m_manager;
		ga_Mixer* m_mixer;
	public:
		SoundManager();
		~SoundManager();
		void update();
	};
}}
