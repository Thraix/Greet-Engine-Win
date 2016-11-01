#pragma once

#include <graphics/textures/texture.h>
#include <math/maths.h>
#include <graphics/sprite.h>

namespace greet { namespace graphics{
	class Animation : public Sprite
	{
	private:
		math::vec2 m_add;

		uint m_image;
		uint m_images;
		bool m_horizontalRead;
		float m_frameTime;
		float m_frameTimer;
		math::vec2 m_texPos2;
	public:

	public:
		Animation(Texture2D* texture, math::vec2 texPos, math::vec2 texSize, float frameTimer, uint images, bool horizontalRead);
		Animation(const Sprite& sprite, float frameTimer, uint images, bool horizontalRead);
		~Animation();

		bool update(float elapsedTime);

		void setTexPos(math::vec2 texSize);
		
		inline const math::vec2& getTexPos() const override { return m_texPos2; }
	};
}}
