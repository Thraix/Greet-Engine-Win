#pragma once

#include <utils/log.h>
#include <vector>
#include <graphics/texture.h>

namespace greet {
	namespace managers{
		class TextureManager
		{
		private:
			static std::vector<graphics::Texture*> m_textures;
		public:

			static void add(graphics::Texture* texture);
			static graphics::Texture* get(const std::string& texturename);
			static void destroy();
		private:
			TextureManager(){}
		};
	}
}