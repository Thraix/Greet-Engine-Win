#pragma once

#include <graphics/textures/texture.h>
#include <graphics/sprite.h>
#include <list>
#include <vector>

namespace greet{ namespace graphics {
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
		Sprite* getSprite(std::string name);
		Sprite* getSpriteFromSheet(std::string sheetName, math::vec2 texPos, math::vec2 texSize);
	private:
		void addTexture(BYTE* bits, uint bpp, std::string name);
		void fillTexture(uint x, uint y, BYTE* bits, uint bpp);
		void updateTexture();
	};
}}
