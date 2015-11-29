#pragma once

#include "glyph.h"

namespace greet{ namespace graphics {
	class RenderableGlyph
	{
	private:
		math::vec2 m_pos;
		math::vec2 m_size;
		math::Transform m_transform;

		float m_xPos;
		float m_width;

		const Glyph* m_glyph;

		public:
			RenderableGlyph(const Glyph* glyph, float offset)
				:m_transform(math::Transform())
			{
				math::vec2 pos = glyph->getPosition()*(-1);
				pos.x += offset;
				m_xPos = offset;
				m_width = glyph->getSize().x;
				m_pos = pos;
				m_size = math::vec2(1,1);
				m_glyph = glyph;
				m_transform.translate(pos);
			}
			~RenderableGlyph()
			{
			}
			inline float getXPos() const { return m_xPos; }
			inline float getCharWidth() const { return m_width; }
			inline const math::vec2& getTexPos() const { return m_glyph->getTexPos(); }
			inline const math::vec2& getTexSize() const { return m_glyph->getTexSize(); }
			inline const math::Transform& getTransform() const { return m_transform; }
			inline float getPixelSize() const { return m_glyph->getPixelSize(); }
	};
}}