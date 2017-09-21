#pragma once

#include <graphics/renderable.h>
#include <string>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <internal/Greet_types.h>
#include <graphics/fonts/fontmanager.h>

namespace Greet {

	class Label : public Renderable
	{
		private:
			Font* m_font;
		
		public:
			std::string text;
			vec2 position;
			uint color;
			
			
		public:
			Label(const std::string& text, vec2 pos,Font* font, uint color);
			Label(const std::string& text, vec2 pos,std::string fontname, uint fontsize, uint color);
			
			void submit(Renderer2D* renderer) const override;
			bool update(float timeElapsed) override;

			void setColor(uint c) override { color = c; }
			inline uint getColor() const override { return color;}
			void setPosition(const vec2& pos) override { position = pos; }
			inline const vec2& getPosition() const override { return position;}
			void setSize(const vec2& size) override {  }
			inline const vec2& getSize() const override { return vec2(getWidth(),m_font->getSize());} // TODO: RETURN SIZE OF TEXT
			float getWidth() const;
	};
}
