#pragma once

#include <string>
#include "shader.h"

namespace greet { namespace graphics{ namespace ShaderFactory {

	Shader* LEDShader();
	Shader* DefaultShader();
	Shader* DebugShader();
	Shader* BasicLightShader();
	Shader* SkyboxShader();
}}}