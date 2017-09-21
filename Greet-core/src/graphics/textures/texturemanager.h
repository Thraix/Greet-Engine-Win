#pragma once

#include <logging/log.h>
#include <vector>
#include "texture.h"
#include <graphics/textures/texture2d.h>
#include <graphics/textures/cubemap.h>
#include <utils/errorhandler.h>

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