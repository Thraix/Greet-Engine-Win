#pragma once

#include <greet_types.h>
#include <math\maths.h>

namespace greet{ namespace graphics{
	class Sprite
	{
	public:
		uint m_color;
	protected:
		uint m_texID;
		uint m_width;
		uint m_height;

		math::vec2 m_texPos;
		math::vec2 m_texSize;
	public:
		Sprite()
			: m_texID(0), m_width(0), m_height(0), m_color(0xffffffff), m_texPos(math::vec2(0, 0)), m_texSize(math::vec2(1, 1))
		{

		}

		Sprite(uint color)
			: m_texID(0), m_width(0), m_height(0), m_color(color), m_texPos(math::vec2(0, 0)), m_texSize(math::vec2(1, 1))
		{

		}

		Sprite(uint texID, uint texWidth, uint texHeight, uint color, math::vec2 texPos, math::vec2 texSize)
			:m_texID(texID), m_width(texWidth), m_height(texHeight), m_color(color), m_texPos(texPos), m_texSize(texSize)
		{

		}
		
		virtual bool update(float timeElapsed) { return false; }

		inline uint getTextureID() const { return m_texID; }
		inline uint getWidth() const { return m_width; }
		inline uint getHeight() const { return m_height; }
		inline Sprite* fromSpriteSheet(math::vec2 texPos, math::vec2 texSize) const { return new Sprite(m_texID, m_width*texSize.x, m_height*texSize.y, m_color, m_texPos + texPos*m_texSize, m_texSize*texSize); }
		virtual inline const math::vec2 &getTexPos() const { return m_texPos; }
		inline const math::vec2 &getTexSize() const { return m_texSize; }
	};
}}