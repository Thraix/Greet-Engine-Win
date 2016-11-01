#pragma once

#include <vector>
#include "font.h"
#include <logging/logger.h>
#include <internal/greet_types.h>
#include <utils/errorhandler.h>

namespace greet { namespace graphics {
	class FontManager
	{
	private:
		static std::vector<graphics::Font*> m_fonts;
	public:

		static void add(graphics::Font* font);
		static Font* get(const std::string& fontname, float size);
		static void destroy();
	private:
		FontManager(){}
		static Font* getSize(const std::string& fontname, float size, uint pos);
	};
}}
