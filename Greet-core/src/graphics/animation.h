#pragma once

#include <graphics/textures/texture.h>
#include <math/maths.h>
#include <graphics/sprite.h>

namespace Greet {
	class Animation : public Sprite
	{
	private:
		vec2 m_add;

		uint m_image;
		uint m_images;
		bool m_horizontalRead;
		float m_frameTime;
		float m_frameTimer;
		vec2 m_texPos2;
	public:

	public:
		Animation(Texture2D* texture, vec2 texPos, vec2 texSize, float frameTimer, uint images, bool horizontalRead);
		Animation(const Sprite& sprite, float frameTimer, uint images, bool horizontalRead);
		~Animation();

		bool update(float elapsedTime);

		void setTexPos(vec2 texSize);
		
		inline const vec2& getTexPos() const override { return m_texPos2; }
	};
}
