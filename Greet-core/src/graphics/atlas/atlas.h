#pragma once

#include <graphics/textures/texture.h>
#include <graphics/sprite.h>
#include <list>
#include <vector>

namespace greet{ namespace graphics {
	class Atlas
	{
	private:
		std::vector<std::string> m_textureNames;
		std::vector<uint> m_textureNamePos;
		std::vector<bool> m_occupied;
		std::string m_name;

		uint m_atlasSize;
		uint m_textureSize;
		uint m_texturesSide;
		uint m_textures;

		BYTE* m_bits;
		uint m_texID;
	public:
		Atlas(std::string atlasName, uint atlasSize, uint textureSize);
		~Atlas();
		bool addTexture(std::string name, std::string filePath);
		void removeTexture(std::string textureName);
		Sprite* getSprite(std::string name);
		Sprite* getSpriteFromSheet(std::string sheetName, math::vec2 texPos, math::vec2 texSize);
		inline uint getTextureID(){ return m_texID; }
		inline const std::string& getName() const { return m_name; }
	private:
		void addTexture(BYTE* bits, uint bpp, std::string name);
		void fillTexture(uint x, uint y, BYTE* bits, uint bpp);
		void genTexture();
		void updateTexture();
	};
}}
