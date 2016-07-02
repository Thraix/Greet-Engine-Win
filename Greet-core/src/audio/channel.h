#pragma once

#include <string>
#include <utils/stringutils.h>

namespace greet{ namespace audio{

	struct Channel
	{	
		std::string m_name;
		float m_volume;
		float m_pitch;
		float m_pan;

		Channel(std::string name, float volume, float pitch, float pan);
		Channel(std::string name, float volume);
		Channel(std::string name);

		void setVolume(float volume);
		void setPitch(float pitch);
		void setPan(float pan);

		inline const std::string& getName() const { return m_name; }
		inline const float getVolume() const  { return m_volume; }
		inline const float getPitch() const  { return m_pitch; }
		inline const float getPan() const  { return m_pan; }
	};
}}