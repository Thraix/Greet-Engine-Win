#pragma once

#include <math/Maths.h>
#include <graphics/shaders/Shader.h>
#include <string.h>

namespace Greet {
	class Light
	{
	public:
		vec3 position;
		uint color;

	public:
		Light(vec3 position, uint color) : position(position) , color(color) {}

		void setToUniform(Shader* shader, const std::string& prefix)
		{
			shader->setUniform3f((prefix + "_position").c_str(), position);
			vec3 color1 = vec3(((color & 0xff0000) >> 16) / 255.0f, ((color & 0xff00) >> 8) / 255.0f, (color & 0xff) / 255.0f);
			shader->setUniform3f((prefix + "_color").c_str(), color1);
		}

	};
}