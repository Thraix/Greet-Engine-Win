#pragma once

#include <graphics/renderables/Renderable.h>
#include <string>
#include <math/Maths.h>
#include <graphics/fonts/Font.h>
#include <internal/GreetTypes.h>
#include <graphics/fonts/FontManager.h>
#include <graphics/renderables/Renderable2D.h>

namespace Greet {

	class Label : public Renderable
	{
		private:
			Font* m_font;
		
		public:
			std::string text;
			Vec2 position;
			uint color;
			
			
		public:
			Label(const std::string& text, Vec2 pos,Font* font, uint color);
			Label(const std::string& text, Vec2 pos,std::string fontname, uint fontsize, uint color);
			
			void Submit(BatchRenderer2D* renderer) const override;
			bool Update(float timeElapsed) override;

			void SetColor(uint c) { color = c; }
			inline uint GetColor() const { return color;}
			void SetPosition(const Vec2& pos) { position = pos; }
			inline const Vec2& GetPosition() const { return position;}
			void SetSize(const Vec2& size) {  }
			inline const Vec2& GetSize() const { return Vec2(GetWidth(),m_font->GetSize());} // TODO: RETURN SIZE OF TEXT
			float GetWidth() const;
			void Draw(BatchRenderer2D* renderer) const { Log::Error("Need to draw Label"); }
			int GetVertexSize() const { return sizeof(Renderable2DVertex); }
	};
}
