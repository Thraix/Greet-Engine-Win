#pragma once

#include <vector>
#include <logging/Log.h>
#include <internal/GreetTypes.h>
#include <utils/ErrorHandler.h>
#include <graphics/fonts\Font.h>

namespace Greet {
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
}
