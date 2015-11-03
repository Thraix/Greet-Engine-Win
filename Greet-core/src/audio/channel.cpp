#include "channel.h"

#include <managers/soundmanager.h>

namespace greet{ namespace audio{

	Channel::Channel(std::string name, float volume, float pitch, float pan)
		: m_name(name), m_volume(volume), m_pitch(pitch), m_pan(pan)
	{

	}

	Channel::Channel(std::string name, float volume)
		: m_name(name), m_volume(volume), m_pitch(1), m_pan(0)
	{

	}

	Channel::Channel(std::string name)
		: m_name(name), m_volume(1), m_pitch(1), m_pan(0)
	{

	}

	void Channel::setVolume(float volume)
	{
		m_volume = volume;
	}

	void Channel::setPitch(float pitch)
	{
		m_pitch = pitch;
	}

	void Channel::setPan(float pan)
	{
		m_pan = pan;
	}
}}