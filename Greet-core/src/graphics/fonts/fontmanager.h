#pragma once

#include <vector>
#include <logging/log.h>
#include <internal/greet_types.h>
#include <utils/errorhandler.h>
#include <graphics\fonts\font.h>

namespace greet { namespace graphics {
	class FontManager
	{
	private:
		static std::vector<FontContainer*> m_fonts;
	public:

		static void add(FontContainer* font);
		static Font* get(const std::string& fontname, uint size);
		static void destroy();
	private:
		FontManager(){}
	};
}}
