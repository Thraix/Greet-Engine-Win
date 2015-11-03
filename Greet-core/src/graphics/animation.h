#pragma once

#include <graphics\texture.h>
#include <math/maths.h>
#include <graphics\sprite.h>

namespace greet { namespace graphics{
	class Animation : public Sprite
	{
	private:
		math::vec2 m_add;

		int m_image;
		int m_images;
		bool m_horizontalRead;
		float m_frameTime;
		float m_frameTimer;
		math::vec2 m_texPos2;
	public:

	public:
		Animation(uint texID, uint texWidth, uint texHeight, uint color, math::vec2 texPos, math::vec2 texSize, float frameTimer, int images, bool horizontalRead);
		Animation(uint color);
		Animation(const Sprite& sprite, float frameTimer, int images, bool horizontalRead);
		~Animation();

		bool update(float elapsedTime);

		void setTexPos(math::vec2 texSize);
		
		inline const math::vec2& getTexPos() const override { return m_texPos2; }
	};
}}