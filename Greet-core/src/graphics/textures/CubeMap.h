#pragma once

#include <string>
#include <internal/GreetTypes.h>
#include <graphics/textures/Texture.h>
#include <utils/ImageUtils.h>

namespace Greet {

	class CubeMap : public Texture
	{
	public:
		CubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back, const std::string& name);
		CubeMap(const std::string& map, const std::string& name);
		CubeMap(uint texId, const std::string& name);
	private:
		void LoadCubeMap(const std::string& image);
		void LoadCubeMap(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back);
		void LoadParameters();
		void LoadImage(const std::string& image, uint mapLocation);
		void LoadImage(BYTE* bits, uint width, uint height, uint bpp, uint mapLocation);
	};
}