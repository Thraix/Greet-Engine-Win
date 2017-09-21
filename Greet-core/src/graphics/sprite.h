#pragma once

#include <internal/Greet_types.h>
#include <math/maths.h>
#include <graphics/textures/texture2d.h>

namespace Greet{
	class Sprite
	{
	protected:
		Texture2D* m_texture;
		vec2 m_texPos;
		vec2 m_texSize;
	public:
		Sprite()
			: m_texture(NULL), m_texPos(vec2(0, 0)), m_texSize(vec2(1, 1))
		{

		}

		Sprite(Texture2D* texture)
			: m_texture(texture), m_texPos(vec2(0, 0)), m_texSize(vec2(1, 1))
		{
		
		}

		Sprite(Texture2D* texture, vec2 texPos, vec2 texSize)
			: m_texture(texture), m_texPos(texPos), m_texSize(texSize)
		{

		}
		
		virtual ~Sprite() {}

		virtual bool update(float timeElapsed) { return false; }

		inline uint getTextureID() const { return m_texture==NULL ? 0 : m_texture->getTexId(); }

		inline Sprite* fromSpriteSheet(vec2 texPos, vec2 texSize) const { return new Sprite(m_texture,m_texPos + texPos*m_texSize, m_texSize*texSize); }
		virtual inline const vec2& getTexPos() const { return m_texPos; }
		inline const vec2& getTexSize() const { return m_texSize; }
	};
}
