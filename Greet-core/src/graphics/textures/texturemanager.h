#pragma once

#include <logging/Log.h>
#include <vector>
#include "Texture.h"
#include <graphics/textures/Texture2D.h>
#include <graphics/textures/CubeMap.h>
#include <utils/ErrorHandler.h>

namespace Greet {
	class TextureManager
	{
	private:
		static std::vector<Texture*> m_textures;
	public:

		static void add(Texture* texture);
		static Texture* get(const std::string& texturename);
		static Texture2D* get2D(const std::string& texturename);
		static CubeMap* get3D(const std::string& texturename);
		static void destroy();
	private:
		TextureManager(){}
	};
}