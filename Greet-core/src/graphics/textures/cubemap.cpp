#include "cubemap.h"

namespace greet { namespace graphics {
	CubeMap::CubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back)
	{
		loadCubeMap(top, bottom, left, right, front, back);
	}

	CubeMap::~CubeMap()
	{
		glDeleteTextures(1, &textureId);
	}

	void CubeMap::loadCubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back)
	{
		glActiveTexture(GL_TEXTURE0);
		textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP,textureId);

		loadImage(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		loadImage(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		loadImage(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		loadImage(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		loadImage(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		loadImage(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void CubeMap::loadImage(const std::string& image, uint mapLocation)
	{
		uint width;
		uint height;
		uint bpp;
		BYTE* bits;
		bits = utils::loadImage(image.c_str(), &width, &height, &bpp);
		utils::flipImage(bits,width,height,bpp);
		glTexImage2D(mapLocation, 0, bpp == 32 ? GL_RGBA : GL_RGB, width, height, 0, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits);
		delete[] bits;
	}
}}