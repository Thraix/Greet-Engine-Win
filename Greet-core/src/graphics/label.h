#pragma once

#include <string>
#include <vector>
#include <managers/fontmanager.h>
#include "renderable2d.h"
#include "renderableglyph.h"

namespace greet{ namespace graphics{
	class Label : public Renderable
	{
	private:
		math::mat3 m_matrix;
		math::mat3 m_shadowMatrix;

		uint m_shadowColor;
		uint m_color;
		float m_size;
		math::vec2 m_pos;
		int m_texID;
		Font* m_font;
		math::mat3 m_transform;
		math::mat3 m_shadowTransform;

		std::vector<RenderableGlyph*> m_glyphs;

	private:
		void clearVector();
		void calibrateMatrices();
	public:
		Label(std::string text, std::string fontname, math::vec2 pos, uint color, float size);
		Label::Label(std::string text, Font* font, math::vec2 pos, uint color, float size);
		~Label();
		void submit(Renderer2D* renderer) const override;
	
		void setText(std::string text);
		void setColor(uint color);
		void setPos(math::vec2 pos);
		void setSize(float size);
		void centerText();
		void centerTextX();
		void centerTextY();
		bool update(float timeElapsed) override;

		float getWidth();
		inline math::vec2 getPos() { return m_pos; }

		inline const std::vector<RenderableGlyph*>& getGlyphs() const { return m_glyphs; }
		inline const int getTextureID() const { return m_texID; }
		inline const uint getColor() const { return m_color; }
		inline const uint getShadowColor() const { return m_shadowColor; }
		inline float getSize() { return m_size; }
		inline const math::mat3& getShadowTransform() const { return m_shadowTransform; }
		inline const math::mat3& getTransform() const { return m_transform; }
		inline const Font &getFont() { return *m_font; }
	};
}}