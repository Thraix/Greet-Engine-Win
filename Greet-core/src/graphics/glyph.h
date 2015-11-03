#pragma once

#include <math/vec2.h>
#include <vector>


namespace greet{ namespace graphics{
	class Glyph
	{
	private:
		math::vec2 m_texPos;
		math::vec2 m_texSize;
		math::vec2 m_pos;
		math::vec2 m_size;
		float m_pixelsize;
		unsigned char m_char;

	public:
		Glyph(math::vec2 pos1, math::vec2 pos2, math::vec2 texPos, float glyphsize, unsigned char c)
		{
			m_pos = pos1/glyphsize;
			m_pos.y = 0;
			m_size = (pos2 - pos1) / glyphsize;
			m_size.y = 0;
			m_texPos = texPos;
			m_texSize = math::vec2(1.0f / 16.0f, 1.0f / 16.0f);
			m_char = c;
			m_pixelsize = 1.0f / glyphsize;
		}
		~Glyph()
		{

		}
		inline float getPixelSize() const { return m_pixelsize; }
		inline const math::vec2& getPosition() const { return m_pos; }
		inline const math::vec2& getSize() const { return m_size; }
		inline const math::vec2& getTexPos() const { return m_texPos; }
		inline const math::vec2& getTexSize() const { return m_texSize; }
	};
}}