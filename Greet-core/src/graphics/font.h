#pragma once

#include <math/vec4.h>
#include "texture.h"
#include "glyph.h"
#include <iostream>
#include <string>
#include <vector>
#include <utils/fileutils.h>
#include <utils/utils.h>
#include <utils/log.h>
#include <math/vec2.h>

namespace greet{ namespace graphics{
	class Font
	{
	private:
		Texture* m_texture;
		std::vector<Glyph*> m_glyphCoords;
		float m_glyphSizes;
		uint m_width;
		uint m_height;
		std::string m_name;
		float m_capY;
		float m_capHeight;
	private:
		bool checkValid(uint bpp, std::string filename);
		std::string readFile(std::string filename, BYTE* bits);
		bool loadFont(std::string glyphs, std::string filename);
		std::string generateGlyphs(const std::string& glyph_file, BYTE* bits, int width, int height);
		std::vector<float> getData(std::string s);
		void destroy();
	public:
		inline math::vec2 getCoordOfGlyph(unsigned char c) const { return math::vec2((int)(c % 16) / 16.0f, ((int)(c / 16.0f)) / 16.0f); }
		Font(const std::string& filename, const std::string& name);
		~Font();
		inline GLuint getTextureID() const { return m_texture==nullptr?0:m_texture->getTexID(); };
		inline const Glyph& getGlyph(unsigned char c) const { return *m_glyphCoords[c<m_glyphCoords.size() ? c : 0]; };
		inline float getPixelSize() const { return 16.0f / m_width; };
		inline const std::string& getName() const { return m_name; }
		inline float getCapY() const { return m_capY; }
		inline float getCapHeight() const { return m_capHeight; }
	};
}}