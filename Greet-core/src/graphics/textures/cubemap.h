#pragma once

#include <string>
#include <internal/greet_types.h>
#include <internal/greetgl.h>
#include <utils/imageutils.h>
#include <graphics/textures/texture.h>

namespace greet { namespace graphics {

	class CubeMap : public Texture
	{
	public:
		CubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back, const std::string& name);
		CubeMap(const std::string& map, const std::string& name);
		CubeMap(uint texId, const std::string& name);
	private:
		void loadCubeMap(const std::string& image);
		void loadCubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back);
		void loadParameters();
		void loadImage(const std::string& image, uint mapLocation);
		void loadImage(BYTE* bits, uint width, uint height, uint bpp, uint mapLocation);
	};
}}