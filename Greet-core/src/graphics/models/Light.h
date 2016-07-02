#pragma once

#include <math/maths.h>
#include <graphics/shaders/shader.h>
#include <string.h>

namespace greet { namespace model {
	class Light
	{
	public:
		math::vec3 position;
		uint color;

	public:
		Light(math::vec3 position, uint color) : position(position) , color(color) {}

		void setToUniform(graphics::Shader* shader, const std::string& prefix)
		{
			shader->setUniform3f((prefix + "_position").c_str(), position);
			math::vec3 color1 = math::vec3(((color & 0xff0000) >> 16) / 255.0f, ((color & 0xff00) >> 8) / 255.0f, (color & 0xff) / 255.0f);
			shader->setUniform3f((prefix + "_color").c_str(), color1);
		}

	};
} }