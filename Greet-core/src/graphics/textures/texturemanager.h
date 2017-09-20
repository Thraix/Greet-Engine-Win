#pragma once

#include <logging/log.h>
#include <vector>
#include "texture.h"
#include <graphics/textures/texture2d.h>
#include <graphics/textures/cubemap.h>
#include <utils/errorhandler.h>

namespace greet {
	namespace graphics{
		class TextureManager
		{
		private:
			static std::vector<graphics::Texture*> m_textures;
		public:

			static void add(graphics::Texture* texture);
			static graphics::Texture* get(const std::string& texturename);
			static graphics::Texture2D* get2D(const std::string& texturename);
			static graphics::CubeMap* get3D(const std::string& texturename);
			static void destroy();
		private:
			TextureManager(){}
		};
	}
}