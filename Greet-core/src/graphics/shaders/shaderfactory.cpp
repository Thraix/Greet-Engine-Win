#include "shader.h"

namespace greet {namespace graphics{namespace ShaderFactory {

	const char* default_shader_vert =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec2 position;\n"
		"layout(location = 1) in vec2 texCoord;\n"
		"layout(location = 2) in float texID;\n"
		"layout(location = 3) in vec4 color;\n"
		"layout(location = 4) in vec2 selfVertex;\n"
		"\n"
		"uniform mat3 pr_matrix;\n"
		"uniform mat3 ml_matrix = mat3(1.0);\n"
		"\n"
		"out DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} vs_out;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(pr_matrix * ml_matrix * vec3(position, 1.0), 1.0);\n"
		"	vs_out.pos = vec2(ml_matrix * vec3(position, 1.0));\n"
		"	vs_out.texCoord = vec2(texCoord.x, 1 - texCoord.y);\n"
		"	vs_out.texID = texID;\n"
		"	vs_out.color = vec4(color.z, color.y, color.x, color.w);\n"
		"	vs_out.coord = selfVertex;"
		"}\n"
	};

	const char *default_shader_frag =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = fs_in.color;\n"
		"	if (fs_in.texID>0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.texID - 0.5);\n"
		"		color *= texture(textures[tid], fs_in.texCoord);\n"
		"		//color = vec4(fs_in.texCoord.xy,0.0,1.0);\n"
		"	}\n"
		"	//else\n"
		"	//{\n"
		"	//	color = vec4(1.0,1.0,1.0,1.0);\n"
		"	//}\n"
		"}\n"
	};

	const char *gradient_shader_frag =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = fs_in.color;\n"
		"	if (fs_in.texID>0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.texID - 0.5);\n"
		"		color *= texture(textures[tid], fs_in.texCoord);\n"
		"	}\n"
		"	color = vec4(color.rgb*(fs_in.coord.y*0.2+0.8),color.a);\n"
		"}\n"
	};

	const char *debug_shader_frag =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(fs_in.coord,1.0,1.0);"
		"}\n"
	};

	const char *led_shader_frag =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = fs_in.color;\n"
		"	if (fs_in.texID>0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.texID - 0.5);\n"
		"		color *= texture(textures[tid], fs_in.texCoord);\n"
		"	}\n"
		"highp int x = int(gl_FragCoord.x) % 2;\n"
		"highp int y = int(gl_FragCoord.y) % 2;\n"
		"if (x == 0 && y == 0)\n"
		"	color = vec4(color.r, 0, 0, color.a);\n"
		"else if (y == 0)\n"
		"	color = vec4(0, color.g, 0, color.a);\n"
		"else if (x == 0)\n"
		"	color = vec4(0, 0, color.b, color.a);\n"
		"}\n"
	};

	const char *basic_light_shader_frag =
	{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"uniform vec2 light_pos;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 pos;\n"
		"	float texID;\n"
		"	vec2 texCoord;\n"
		"	vec4 color;\n"
		"	vec2 coord;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"float intensity = 1.0/pow(length(fs_in.pos - light_pos),0.4f);\n"
		"if (intensity > 1)\n"
		"	intensity = 1;\n"
		"	color = fs_in.color;\n"
		"	if (fs_in.texID>0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.texID - 0.5);\n"
		"		color *= texture(textures[tid], fs_in.texCoord);\n"
		"	}\n"
		"color = vec4(color.rgb*intensity, color.a);\n"
		"}\n"
	};

	Shader* LEDShader()
	{
		return Shader::fromSource("LEDShader", default_shader_vert, led_shader_frag);
	}

	Shader* DefaultShader()
	{
		return Shader::fromSource("defaultShader", default_shader_vert, default_shader_frag);
	}

	Shader* BasicLightShader()
	{
		return Shader::fromSource("basicLightShader", default_shader_vert, basic_light_shader_frag);
	}
	Shader* DebugShader()
	{
		return Shader::fromSource("debugShader", default_shader_vert, debug_shader_frag);
	}

	Shader* GradientShader()
	{
		return Shader::fromSource("gradientShader", default_shader_vert, gradient_shader_frag);
	}
}}}