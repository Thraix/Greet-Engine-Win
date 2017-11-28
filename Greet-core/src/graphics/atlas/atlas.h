#pragma once

#include <graphics/textures/Texture.h>
#include <graphics/Sprite.h>
#include <list>
#include <vector>

namespace Greet{
	class Atlas : public Texture2D
	{
	private:
		std::vector<std::string> m_textureNames;
		std::vector<uint> m_textureNamePos;
		std::vector<bool> m_occupied;

		uint m_textureSize;
		uint m_texturesSide;
		uint m_textures;

		BYTE* m_bits;
	public:
		Atlas(std::string atlasName, uint atlasSize, uint textureSize);
		~Atlas();
		bool addTexture(std::string name, std::string filePath);
		void removeTexture(std::string textureName);
		void addTexture(BYTE* bits, uint bpp, std::string name);
		Sprite* getSprite(std::string name);
		Sprite* getSpriteFromSheet(std::string sheetName, vec2 texPos, vec2 texSize);
	private:
		void fillTexture(uint x, uint y, BYTE* bits, uint bpp);
		void updateTexture();
	};
}
