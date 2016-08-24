#pragma once

#include <internal/greetgl.h>
#include <internal/greet_types.h>
#include <graphics/textures/texture.h>
#include <string>
#include <math/maths.h>
#include <logging/logger.h>

namespace greet{ namespace graphics{
	class Font
	{
	private:
		ftgl::texture_atlas_t* m_atlas;
		ftgl::texture_font_t* m_font;
		float m_size;
		const byte* m_data;
		uint m_datasize;
		std::string m_name;
		std::string m_filename;
		math::vec2 m_scale;
		
	public:
		Font(std::string filename, std::string name, float size);
		Font(const byte* data, uint datasize, std::string name, float size);
		inline ftgl::texture_font_t* getFTFont() const { return m_font;}
		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_filename; }
		inline const byte* getData() const { return m_data;}
		inline uint getDataSize() const { return m_datasize;}
		inline float getSize() const {return m_size;}
		inline uint getAtlasID() const {return m_atlas->id;}
		float getWidthOfText(const std::string& text) const;
		inline const math::vec2& getScale() const {return m_scale;}
		void setScale(const math::vec2& scale) { m_scale = scale;}
	};
}}