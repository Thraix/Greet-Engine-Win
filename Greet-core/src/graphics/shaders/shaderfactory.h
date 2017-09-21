#pragma once

#include <string>
#include "shader.h"

namespace Greet { namespace ShaderFactory {

	Shader* LEDShader();
	Shader* DefaultShader();
	Shader* DebugShader();
	Shader* BasicLightShader();
	Shader* SkyboxShader();
}}