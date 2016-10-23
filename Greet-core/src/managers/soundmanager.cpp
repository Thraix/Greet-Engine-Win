#include "soundmanager.h"

#define GAU_THREAD_POLICY_MULTI 2

namespace greet{ namespace managers {

	SoundManager::SoundManager()
		: Manager<audio::Sound>("SOUNDMANGER")
	{
		gc_initialize(0);
		m_manager = gau_manager_create();
		m_mixer = gau_manager_mixer(m_manager);
	}

	SoundManager::~SoundManager()
	{
		gau_manager_destroy(m_manager);
		gc_shutdown();
	}

	void SoundManager::update()
	{
		gau_manager_update(m_manager);
	}

}}