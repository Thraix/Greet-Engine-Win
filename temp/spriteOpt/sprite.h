#pragma once


#include "renderable2d.h"
#include <managers\texturemanager.h>
namespace greet{ namespace graphics{
	class Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(float x, float y, float width, float height, uint color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		Sprite(float x, float y, float width, float height, Texture* texture, float texX, float texY, float texWidth, float texHeight, uint color);
		Sprite(float x, float y, float width, float height, const std::string& textureName);
		Sprite(float x, float y, float width, float height, const std::string& textureName, float texX, float texY, float texWidth, float texHeight, uint color);

	};
}}