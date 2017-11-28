#pragma once

#include <string>
#include <internal/GreetTypes.h>
#include <internal/GreetGL.h>
#include <utils/ImageUtils.h>
#include <graphics/textures/Texture.h>

namespace Greet {

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
}