#include "sprite.h"

namespace greet{ namespace graphics{
	Sprite::Sprite(float x, float y, float width, float height, uint color)
		: Renderable2D(math::vec2(x, y), math::vec2(width,height), color)
	{

	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(math::vec2(x, y), math::vec2(width, height), 0xffffffff, texture)
	{

	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture, float texX, float texY, float texWidth, float texHeight, uint color)
		: Renderable2D(math::vec2(x, y), math::vec2(width, height), color, texture, math::vec2(texX, texY), math::vec2(texWidth, texHeight))
	{

	}

	Sprite::Sprite(float x, float y, float width, float height, const std::string& textureName)
		: Renderable2D(math::vec2(x, y), math::vec2(width, height), 0xffffffff, managers::TextureManager::get(textureName))
	{

	}
	Sprite::Sprite(float x, float y, float width, float height, const std::string& textureName, float texX, float texY, float texWidth, float texHeight, uint color)
		: Renderable2D(math::vec2(x, y), math::vec2(width, height), color, managers::TextureManager::get(textureName), math::vec2(texX, texY), math::vec2(texWidth, texHeight))
	{

	}

}}