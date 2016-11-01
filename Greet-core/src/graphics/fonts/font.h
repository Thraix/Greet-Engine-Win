#pragma once

#include <internal/greetgl.h>
#include <internal/greet_types.h>
#include <graphics/textures/texture.h>
#include <string>
#include <math/maths.h>
#include <logging/logger.h>
#include <graphics/fonts/fontcontainer.h>

namespace greet{ namespace graphics{


	class Font
	{
	private:
		FontContainer* m_container;
		ftgl::texture_atlas_t* m_atlas;
		ftgl::texture_font_t* m_font;
		float m_size;
		
	public:
		Font(FontContainer* container, uint size);
		Font(FontContainer* container, uint size, math::vec2 scale);
		void init();
		inline ftgl::texture_font_t* getFTFont() const { return m_font;}
		inline float getSize() const {return m_size;}
		inline uint getAtlasID() const {return m_atlas->id;}
		float getWidthOfText(const std::string& text) const;
	};
}}