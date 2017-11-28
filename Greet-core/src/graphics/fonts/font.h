#pragma once

#include <internal/GreetGL.h>
#include <internal/GreetTypes.h>
#include <graphics/textures/Texture.h>
#include <string>
#include <math/Maths.h>
#include <logging/Log.h>
#include <graphics/fonts/FontContainer.h>

namespace Greet{


	class Font
	{
	private:
		FontContainer* m_container;
		ftgl::texture_atlas_t* m_atlas;
		ftgl::texture_font_t* m_font;
		float m_size;
		
	public:
		Font(FontContainer* container, uint size);
		Font(FontContainer* container, uint size, vec2 scale);
		void init();
		inline ftgl::texture_font_t* getFTFont() const { return m_font;}
		inline float getSize() const {return m_size;}
		inline uint getAtlasID() const {return m_atlas->id;}
		float getWidthOfText(const std::string& text, uint startPos, uint endPos) const;
		float getWidthOfText(const std::string& text) const;
		float* Font::getPartialWidths(const std::string& text);
	};
}