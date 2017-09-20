#include "sound.h"

#include "soundmanager.h"

namespace greet { namespace audio{
	
	Sound::Sound(const std::string& filename, const std::string& name, std::string channelName)
		: m_name(name), m_channel(ChannelManager::get(channelName)), m_playing(false)
	{
		std::vector<std::string> split = utils::split_string(filename,".");
		if (split.size() < 2){
			Log::error("Invalid file name: ", filename.c_str());
			return;
		}
		m_sound = gau_load_sound_file(("res/sounds/" + filename).c_str(), split.back().c_str());
		if (m_sound == nullptr)
		{
			Log::error("Could not load file: ", filename.c_str());
			return;
		}

	}

	Sound::Sound(const std::string& filename, const std::string& name, Channel* channel)
		: m_name(name), m_channel(channel), m_playing(false)
	{
		m_sound = gau_load_sound_file(("res/sounds/" + filename).c_str(),"wav");
	}

	Sound::~Sound()
	{
		ga_sound_release(m_sound);
	}

	void Sound::play()
	{ 
		gc_int32 quit = 0;
		m_handle = gau_create_handle_sound(SoundManager::m_mixer, m_sound, &destroy_on_finish, &quit, NULL);
		m_handle->sound = this;
		refreshChannel();
		m_playing = true;
		ga_handle_play(m_handle);
	}

	void Sound::loop()
	{
		gc_int32 quit = 0;
		m_handle = gau_create_handle_sound(SoundManager::m_mixer, m_sound, &loop_on_finish, &quit, NULL);
		m_handle->sound = this;
		m_playing = false;
		refreshChannel();
		m_playing = true;
		ga_handle_play(m_handle);
	}

	void Sound::pause()
	{
		if (!m_playing)
			return;

		m_playing = false;
		ga_handle_stop(m_handle);
	}

	void Sound::resume()
	{
		if (m_playing)
			return;

		m_playing = true;
		ga_handle_play(m_handle);
	}

	void Sound::stop()
	{
		if (!m_playing)
			return;

		ga_handle_stop(m_handle);
		//ga_handle_destroy(m_handle);
		m_playing = false;
	}

	void Sound::refreshChannel()
	{
		if (m_playing)
			return;
		ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_GAIN, m_channel->getVolume());
		ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_PITCH, m_channel->getPitch());
		ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_PAN, m_channel->getPan());
	}

	void Sound::destroy_on_finish(ga_Handle* in_handle, void* in_context)
	{
		ga_handle_destroy(in_handle);
		((Sound*)in_handle->sound)->stop();
	}

	void Sound::loop_on_finish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->loop();
		ga_handle_destroy(in_handle);
	}

}}
