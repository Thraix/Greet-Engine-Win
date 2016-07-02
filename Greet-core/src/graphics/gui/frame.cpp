#include "frame.h"

namespace greet { namespace graphics {
	using namespace utils;
	Frame::Frame(const math::vec2& position, const math::vec2& size, const std::string& title)
	: GUI(position,size)
	{
		m_label = new Label(title,math::vec2(0,-8),"anonymous",16, ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f, 3)));
		//m_border = new Border(math::vec2(0,0),size,BorderData::getDefaultBorderData());
		m_frameHeader = new Renderable2D(math::vec2(0,0),math::vec2(size.x, 30),ColorUtils::vec3ToColorHex(ColorUtils::getMaterialColor(120 / 360.0f,9)),NULL);
		Group::add(m_frameHeader);
		GUI::add(m_label);
	}
}}
