#pragma once

#include <internal/greet_types.h>
#include <math/maths.h>
#include <graphics/textures/texture2d.h>

namespace greet{ namespace graphics{
	class Sprite
	{
	protected:
		Texture2D* m_texture;
		math::vec2 m_texPos;
		math::vec2 m_texSize;
	public:
		Sprite()
			: m_texture(NULL), m_texPos(math::vec2(0, 0)), m_texSize(math::vec2(1, 1))
		{

		}

		Sprite(Texture2D* texture)
			: m_texture(texture), m_texPos(math::vec2(0, 0)), m_texSize(math::vec2(1, 1))
		{
		
		}

		Sprite(Texture2D* texture, math::vec2 texPos, math::vec2 texSize)
			: m_texture(texture), m_texPos(texPos), m_texSize(texSize)
		{

		}
		
		virtual ~Sprite() {}

		virtual bool update(float timeElapsed) { return false; }

		inline uint getTextureID() const { return m_texture==NULL ? 0 : m_texture->getTexId(); }

		inline Sprite* fromSpriteSheet(math::vec2 texPos, math::vec2 texSize) const { return new Sprite(m_texture,m_texPos + texPos*m_texSize, m_texSize*texSize); }
		virtual inline const math::vec2& getTexPos() const { return m_texPos; }
		inline const math::vec2& getTexSize() const { return m_texSize; }
	};
}}
