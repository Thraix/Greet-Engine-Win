#pragma once

#include <string>
#include <utils/stringutils.h>

namespace Greet{

	struct AudioChannel
	{	
		std::string m_name;
		float m_volume;
		float m_pitch;
		float m_pan;

		AudioChannel(std::string name, float volume, float pitch, float pan);
		AudioChannel(std::string name, float volume);
		AudioChannel(std::string name);

		void setVolume(float volume);
		void setPitch(float pitch);
		void setPan(float pan);

		inline const std::string& getName() const { return m_name; }
		inline const float getVolume() const  { return m_volume; }
		inline const float getPitch() const  { return m_pitch; }
		inline const float getPan() const  { return m_pan; }
	};
}