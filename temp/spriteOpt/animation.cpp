#include "animation.h"

namespace greet { namespace graphics{

	Animation::Animation(std::string textureName, math::vec2 texPos, math::vec2 texSize, float frameTimer, int images, bool horizontalRead)
		:m_texture(managers::TextureManager::get(textureName)), m_texPos(texPos), m_texSize(texSize), m_frameTimer(frameTimer), m_frameTime(frameTimer), m_images(images), m_image(0), m_color(0xffffffff)
	{
		m_add = math::vec2(horizontalRead ? texSize.x : 0.0f, horizontalRead ? 0.0f : texSize.y);
	}

	Animation::Animation(uint color)
		: m_texture(nullptr), m_texPos(math::vec2(0, 0)), m_texSize(math::vec2(1, 1)), m_frameTimer(1), m_frameTime(1), m_images(1), m_image(1), m_color(color)
	{
		m_add = math::vec2(0.0f,0.0f);
	}

	Animation::Animation(Texture* texture, math::vec2 texPos, math::vec2 texSize, float frameTimer, int images, bool horizontalRead)
		: m_texture(texture), m_texPos(texPos), m_texSize(texSize), m_frameTimer(frameTimer), m_frameTime(frameTimer), m_images(images), m_image(0), m_color(0xffffffff)
	{
		m_add = math::vec2(horizontalRead ? texSize.x : 0.0f, horizontalRead ? 0.0f : texSize.y);
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
			return true;
		}
		return false;
	}

	void Animation::setTexCoords(math::vec2 texPos, math::vec2 texSize)
	{
		m_texPos = texPos;
		m_texSize = texSize;
	}

	void Animation::setTexSize(math::vec2 texPos)
	{
		m_texPos = texPos;
	}

	void Animation::setTexPos(math::vec2 texSize)
	{
		m_texSize = texSize;
	}
}}