#include "atlas.h"

namespace greet { namespace graphics{
	Atlas::Atlas(std::string atlasName, uint atlasSize, uint textureSize)
		:m_name(atlasName), m_atlasSize(atlasSize), m_textureSize(textureSize), m_texturesSide(m_atlasSize / m_textureSize), m_textures((m_atlasSize / m_textureSize)*(m_atlasSize / m_textureSize))
	{
		GREET_ASSERT(m_atlasSize > m_textureSize, "ATLAS", "Atlas size must be greater than the textures sizes: ", m_name.c_str());
		GREET_ASSERT(!(m_atlasSize == 0) && !(m_atlasSize & (m_atlasSize - 1)),"ATLAS", "Atlas size must be a power of two: ", m_name.c_str());
		GREET_ASSERT(!(m_textureSize == 0) && !(m_textureSize & (m_textureSize - 1)), "ATLAS", "Texture size must be a power of two: ", m_name.c_str());
		uint bits = m_atlasSize * m_atlasSize * 4;

		m_bits = new BYTE[bits];
		for (int i = 0; i < bits; i+=4)
		{
			m_bits[i  ] = 0;
			m_bits[i+1] = 0;
			m_bits[i+2] = 0;
			m_bits[i+3] = 255;
		}
		for (int i = 0; i < m_textures; i++)
		{
			m_occupied.push_back(false);
		}

		genTexture();
	}

	Atlas::~Atlas()
	{

	}

	void Atlas::genTexture()
	{
		glGenTextures(1, &m_texID);

		updateTexture();
	}

	void Atlas::updateTexture()
	{
		glBindTexture(GL_TEXTURE_2D, m_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_atlasSize, m_atlasSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_bits);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool Atlas::addTexture(std::string name, std::string filePath)
	{
		uint textures = m_atlasSize / m_textureSize;
		if (m_textureNames.size() >= textures*textures)
		{
			GREET_ERROR("ATLAS","There is no more room in the Atlas. Increase size or create a new one. ", m_name.c_str());
			return false;
		}
		uint width;
		uint height;
		uint bpp;
		BYTE* bits = utils::loadImage(filePath.c_str(), &width, &height,&bpp);
		if (width != m_textureSize || height != m_textureSize)
		{
			GREET_ERROR("ATLAS","The given textures size is not valid: ",name.c_str()," (",width,",",height,")");
			return false;
		}
		addTexture(bits,bpp,name);

		delete[] bits;

		return true;
	}

	void Atlas::addTexture(BYTE* bits, uint bpp, std::string name)
	{
		uint x = m_texturesSide;
		uint y = m_texturesSide;
		for (uint i = 0; i < m_textures; i++)
		{
			if (!m_occupied[i])
			{
				x = i%m_texturesSide;
				y = (i - x) / m_texturesSide;
				m_textureNames.push_back(name);
				m_textureNamePos.push_back(i);
				m_occupied[i] = true;
				break;
			}
		}
		if (x == m_texturesSide || y == m_texturesSide)
		{
			GREET_ERROR("ATLAS", "There is no more room in the Atlas. Increase size or create a new one. ", m_name.c_str());
			return;
		}

		fillTexture(x,y,bits,bpp);
	}

	void Atlas::fillTexture(uint x, uint y, BYTE* bits, uint bpp)
	{

		uint pos = (x + ((m_texturesSide - y) - 1) * m_atlasSize) * m_textureSize;
		uint j;
		uint k;
		for (uint xx = 0; xx < m_textureSize; xx++)
		{
			for (uint yy = 0; yy < m_textureSize; yy++)
			{
				j = (pos + xx + yy * m_atlasSize) * 4;
				k = (xx + yy * m_textureSize) * 4;
				for (uint i = 0; i < (bpp >> 3); i++)
					m_bits[j + i] = bits[k + i];
			}
		}

		updateTexture();

	}

	Sprite* Atlas::getSprite(std::string name)
	{
		return getSpriteFromSheet(name, math::vec2(0, 0), math::vec2(1, 1));
	}

	Sprite* Atlas::getSpriteFromSheet(std::string sheetName, math::vec2 texPos, math::vec2 texSize)
	{
		uint size = m_textureNames.size();
		for (uint i = 0; i < size; i++)
		{
			if (m_textureNames[i].compare(sheetName)==0)
			{
				uint j = m_textureNamePos[i];
				uint x = j % (m_atlasSize / m_textureSize);
				uint y = (j - x) / (m_atlasSize / m_textureSize);
				float size = (float)m_textureSize / (float)m_atlasSize;
				math::vec2 spriteSize = math::vec2(size,size);
				math::vec2 spritePos = spriteSize*math::vec2(x, y);
				spritePos += texPos * spriteSize;
				spriteSize *= texSize;
				return new Sprite(m_texID, m_textureSize*texSize.x, m_textureSize*texSize.y, spritePos, spriteSize);
			}
		}
		GREET_ERROR("ATLAS", "No texture found in Atlas: ", m_name.c_str(), "(", sheetName.c_str(), ")");
		return new Sprite(m_texID, m_atlasSize, m_atlasSize, math::vec2(0, 0), math::vec2(1, 1));
	}

	void Atlas::removeTexture(std::string textureName)
	{
		uint size = m_textureNames.size();
		for (uint i = 0; i < size; i++)
		{
			if (m_textureNames[i].compare(textureName) == 0)
			{
				uint j = m_textureNamePos[i];
				m_occupied[j] = false;
				uint bit = m_textureSize*m_textureSize * 4;
				BYTE* bits = new BYTE[bit];
				for (uint ii = 0; ii < bit; ii += 4)
				{
					bits[ii] = 0;
					bits[ii + 1] = 0;
					bits[ii + 2] = 0;
					bits[ii + 3] = 255;
				}
				uint x = j%m_texturesSide;
				uint y = (j - x) / m_texturesSide;
				fillTexture(x,y,bits,32);
				delete[] bits;

				m_textureNames.erase(m_textureNames.begin() + i);
				m_textureNamePos.erase(m_textureNamePos.begin() + i);
				break;
			}
		}
	}
}}