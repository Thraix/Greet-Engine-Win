#pragma once

#include <string.h>
#include "gui.h"
#include "border.h"
#include "label.h"
#include <utils/colorutils.h>

namespace greet { namespace graphics {

	class Frame : public GUI
	{
	private:
		//Border* m_border;
		Renderable2D* m_frameHeader;
		Label* m_label;

	public:
		Frame(const math::vec2& position, const math::vec2& size, const std::string& title);
		math::vec2 getOffsetTL() const override{ return math::vec2(10,30);}
		math::vec2 getOffsetBR() const { return math::vec2(10,10);}

	};

}}
