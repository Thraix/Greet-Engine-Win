#include "font.h"
#include <direct.h>
namespace greet{ namespace graphics{
	Font::Font(std::string filename, std::string name, float size)
	: m_filename(filename),m_data(nullptr),m_datasize(0), m_name(name), m_size(size), m_scale(math::vec2(1.0f,1.0f))
	{
		m_atlas = ftgl::texture_atlas_new(512,512,2);
		m_font = ftgl::texture_font_new_from_file(m_atlas,size,filename.c_str());
		ASSERT(m_font,"Could not load font:",filename); // TODO: RETURN DEFAULT FONT
	}
	
	Font::Font(const byte* data, uint datasize, std::string name, float size)
	: m_filename(""),m_data(data),m_datasize(datasize), m_name(name), m_size(size), m_scale(math::vec2(1.0f,1.0f))
	{
		m_atlas = ftgl::texture_atlas_new(512,512,2);
		m_font = ftgl::texture_font_new_from_memory(m_atlas,size,data,datasize);
		ASSERT(m_font,"Could not load font from memory:",name); // TODO: RETURN DEFAULT FONT
	}
}}