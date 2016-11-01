#pragma once

#include <logging/logger.h>
#include <vector>
#include "texture.h"
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
			static void destroy();
		private:
			TextureManager(){}
		};
	}
}