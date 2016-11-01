#include "animation.h"

namespace greet { namespace graphics{

	Animation::Animation(Texture2D* texture, math::vec2 texPos, math::vec2 texSize, float frameTimer, uint images, bool horizontalRead)
		: Sprite(texture, texPos, texSize), m_frameTimer(frameTimer), m_frameTime(frameTimer), m_images(images), m_image(0)
	{
		m_add = math::vec2(horizontalRead ? texSize.x : 0.0f, horizontalRead ? 0.0f : texSize.y);
		m_texPos2 = m_texPos;
	}

	Animation::Animation(const Sprite& sprite, float frameTimer, uint images, bool horizontalRead)
		: Sprite(sprite), m_frameTimer(frameTimer), m_frameTime(frameTimer), m_images(images), m_image(0)
	{
		m_add = math::vec2(horizontalRead ? m_texSize.x : 0.0f, horizontalRead ? 0.0f : m_texSize.y);
		m_texPos2 = m_texPos;
	}


	Animation::~Animation()
	{

	}

	bool Animation::update(float timeElapsed)
	{
		m_frameTime -= timeElapsed;
		if (m_frameTime <= 0)
		{
			m_image++;
			m_image %= m_images;
			m_frameTime = m_frameTimer + m_frameTime;
			m_texPos2 = m_texPos + m_add * m_image;
			return true;
		}
		return false;
	}

	void Animation::setTexPos(math::vec2 texSize)
	{
		m_texSize = texSize;
	}
}}