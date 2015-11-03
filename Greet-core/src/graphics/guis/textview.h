#pragma once

#include <graphics\label.h>
#include "gui.h"

namespace greet{ namespace graphics {
	class TextView : public GUI
	{
	public:

	protected:
		Label* m_label;
	public:
		TextView(math::vec2 pos, std::string fontname, float size);
		TextView(math::vec2 pos, std::string fontname, float size, std::string text);
		TextView(math::vec2 pos, std::string fontname, float size, std::string text, uint color);

		TextView(math::vec2 pos, Font* font, float size);
		TextView(math::vec2 pos, Font* font, float size, std::string text);
		TextView(math::vec2 pos, Font* font, float size, std::string text, uint color);

		TextView(math::vec2 pos, float size);
		TextView(math::vec2 pos, float size, std::string text);
		TextView(math::vec2 pos, float size, std::string text, uint color);

		void submitComponents(Renderer2D* renderer) const override;
		void setForegroundColor(uint color) override;

		inline void setText(std::string text) { m_label->setText(text); }
		inline void centerText() { centerTextX();centerTextY();}
		inline void centerTextX() { m_label->centerTextX(); GUI::m_pos = m_label->getPos(); }
		inline void centerTextY() { m_label->centerTextY(); GUI::m_pos = m_label->getPos(); }
	protected:
		inline void init();


	};
}}