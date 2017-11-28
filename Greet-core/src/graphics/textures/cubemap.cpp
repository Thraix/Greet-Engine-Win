#include "CubeMap.h"

namespace Greet {
	CubeMap::CubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back, const std::string& name)
		: Texture(name, GL_TEXTURE_CUBE_MAP)
	{
		LoadCubeMap(top, bottom, left, right, front, back);
	}

	CubeMap::CubeMap(const std::string& map, const std::string& name)
		: Texture(name,GL_TEXTURE_CUBE_MAP)
	{
		LoadCubeMap(map);
	}

	CubeMap::CubeMap(uint texId, const std::string& name)
		: Texture(texId, name, GL_TEXTURE_CUBE_MAP)
	{

	}

	void CubeMap::LoadCubeMap(const std::string& image)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_CUBE_MAP,m_texId);

		uint width;
		uint height;
		uint bpp;
		BYTE* bits;
		bits = ImageUtils::loadImage(image.c_str(), &width, &height, &bpp);
		uint w = width / 4;
		uint h = height / 3;
		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,0,h,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,w*2,h,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_NEGATIVE_X);

		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,w,0,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,w,h*2,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);

		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,w,h,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		LoadImage(ImageUtils::cropImage(bits,width,height,bpp,w*3,h,w,h),w,h,bpp,GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
		LoadParameters();
		delete[] bits;
		glBindTexture(GL_TEXTURE_CUBE_MAP,0);

	}

	void CubeMap::LoadCubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_CUBE_MAP,m_texId);

		LoadImage(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		LoadImage(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		LoadImage(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		LoadImage(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		LoadImage(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		LoadImage(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

		LoadParameters();

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void CubeMap::LoadParameters()
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void CubeMap::LoadImage(const std::string& image, uint mapLocation)
	{
		uint width;
		uint height;
		uint bpp;
		BYTE* bits;
		bits = ImageUtils::loadImage(image.c_str(), &width, &height, &bpp);
		LoadImage(bits,width,height,bpp,mapLocation);
	}

	void CubeMap::LoadImage(BYTE* bits, uint width, uint height, uint bpp, uint mapLocation)
	{
		ImageUtils::flipImage(bits,width,height,bpp);
		glTexImage2D(mapLocation, 0, bpp == 32 ? GL_RGBA : GL_RGB, width, height, 0, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits);
		delete[] bits;
		
	}
}