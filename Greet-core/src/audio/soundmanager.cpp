#include "soundmanager.h"

#define GAU_THREAD_POLICY_MULTI 2

namespace greet{ namespace audio {

	gau_Manager* SoundManager::m_manager = nullptr;
	ga_Mixer* SoundManager::m_mixer = nullptr;
	std::vector<audio::Sound*> SoundManager::m_sounds;

	void SoundManager::init()
	{
		gc_initialize(0);
		m_manager = gau_manager_create();
		m_mixer = gau_manager_mixer(m_manager);
	}

	void SoundManager::add(audio::Sound* sound)
	{
		m_sounds.push_back(sound);
	}

	audio::Sound* SoundManager::get(const std::string& soundname)
	{
		uint size = m_sounds.size();

		for (uint i = 0; i < size; i++)
			if (soundname.compare(m_sounds[i]->getName().c_str()) == 0)
				return m_sounds[i];
		LOG_ERROR("SOUNDMANAGER","Could not find the given sound: ", soundname.c_str());
		return m_sounds[0];
	}

	void SoundManager::destroy()
	{
		for (uint i = 0; i < m_sounds.size(); i++)
			delete m_sounds[i];

		gau_manager_destroy(m_manager);
		gc_shutdown();
	}

	void SoundManager::update()
	{
		gau_manager_update(m_manager);
	}

}}