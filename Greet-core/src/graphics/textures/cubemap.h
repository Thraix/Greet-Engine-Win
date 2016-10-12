#pragma once

#include <string>
#include <internal/greet_types.h>
#include <internal/greetgl.h>
#include <utils/imageutils.h>

namespace greet { namespace graphics {

	class CubeMap
	{

	private:
		uint textureId;

	public:
		CubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back);
		CubeMap(const std::string& map);
		~CubeMap();
		inline uint getTextureId() const { return textureId; }
		void enable() const { glBindTexture(GL_TEXTURE_CUBE_MAP,textureId); }
		void disable() const { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }
	private:
		void loadCubeMap(const std::string& image);
		void loadCubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back);
		void loadParameters();
		void loadImage(const std::string& image, uint mapLocation);
		void loadImage(BYTE* bits, uint width, uint height, uint bpp, uint mapLocation);
	};
}}