#include "shader.h"

namespace greet {namespace graphics{namespace ShaderFactory {

	const std::string default_shader_vert =
	#include "default2dshader.vert"
	;

	const std::string& default_shader_frag =
	#include "default2dshader.frag"
	;

	const char *debug_shader_frag =
#include "debugshader.frag"
	;

	const char *led_shader_frag =
	#include "ledshader.frag"
	;

	const char *basic_light_shader_frag =
#include "basiclightshader.frag"
	;

	const std::string skybox_shader_vert =
		#include "skyboxshader.vert"
	;

	const char *skybox_shader_frag = 
		#include "skyboxshader.frag"
	;

	Shader* LEDShader()
	{
		return Shader::fromSource(default_shader_vert, led_shader_frag);
	}

	Shader* DefaultShader()
	{
		return Shader::fromSource(default_shader_vert, default_shader_frag);
	}

	Shader* BasicLightShader()
	{
		return Shader::fromSource(default_shader_vert, basic_light_shader_frag);
	}
	Shader* DebugShader()
	{
		return Shader::fromSource(default_shader_vert, debug_shader_frag);
	}
	
	Shader* SkyboxShader()
	{
		return Shader::fromSource(skybox_shader_vert, skybox_shader_frag);
	}
}}}