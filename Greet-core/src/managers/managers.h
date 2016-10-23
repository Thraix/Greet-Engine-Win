#pragma once
#if 0
#include <managers\manager.h>
#include <audio\channel.h>
#include <managers\soundmanager.h>
#include <graphics/textures/texture.h>
#include <graphics/atlas/atlas.h>
#include <graphics/fonts/font.h>

namespace greet { namespace managers {
	
	Manager<audio::Channel>* ChannelManager = new Manager<audio::Channel>("CHANNELMANAGER");
	SoundManager* soundManager = new SoundManager();
	Manager<graphics::Atlas>* AtlasManager = new Manager<graphics::Atlas>("ATLASMANAGER");
	Manager<graphics::Font>* FontManager = new Manager<graphics::Font>("FONTMANGER");
	Manager<graphics::Texture>* TextureManager = new Manager<graphics::Texture>("TEXTUREMANGER");

	void destroyManagers()
	{
		delete ChannelManager;
		delete soundManager;
		delete AtlasManager;
		delete FontManager;
		delete TextureManager;
	}
}}
#endif