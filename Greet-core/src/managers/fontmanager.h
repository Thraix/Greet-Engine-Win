#pragma once

#include <utils/log.h>
#include <vector>
#include <graphics/font.h>
#include <greet_types.h>

namespace greet { namespace managers{
	class FontManager
	{
	private:
		static std::vector<graphics::Font*> m_fonts;
	public:

		static void add(graphics::Font* font);
		static graphics::Font* get(const std::string& fontname);
		static void destroy();
	private:
		FontManager(){}
	};
}}