#include "shader.h"

#include "shaderfactory.h"
namespace greet {
	namespace graphics {

	Shader::Shader(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc)
	{
		m_shaderID = load(geomSrc, vertSrc, fragSrc,true);
	}

	Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
	{
		m_shaderID = load(vertSrc,fragSrc);
	}

	GLuint Shader::load(const std::string& vertSrc, const std::string& fragSrc)
	{
		return load("", vertSrc, fragSrc, false);
	}

	GLuint Shader::load(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc, bool hasGeometry)
	{
		GLuint program = glCreateProgram();

		uint shader = attachShader(program, vertSrc, GL_VERTEX_SHADER);
		if (shader != 0)
			return shader;
		shader = attachShader(program, fragSrc, GL_FRAGMENT_SHADER);
		if (shader != 0)
			return shader;
		if (hasGeometry)
		{
			attachShader(program, geomSrc, GL_GEOMETRY_SHADER);
			if (shader != 0)
				return shader;
		}
		glLinkProgram(program);
		glValidateProgram(program);


		return program;
	}

	GLuint Shader::attachShader(const GLuint program, const std::string& shaderSrc, const GLuint shaderType)
	{
		GLuint shader = glCreateShader(shaderType);
		const char* src = shaderSrc.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		GLint resultFrag;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &resultFrag);
		if (resultFrag == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			using namespace utils;
			if (shaderType == GL_FRAGMENT_SHADER)
			{
				LOG_ERROR("SHADER", "Failed to compile fragment Shader!\n", &error[0]);
				ErrorHandle::setErrorCode(GREET_ERROR_SHADER_FRAGMENT);
			}
			else if (shaderType == GL_VERTEX_SHADER)
			{
				LOG_ERROR("SHADER", "Failed to compile vertex Shader!\n", &error[0]);
				ErrorHandle::setErrorCode(GREET_ERROR_SHADER_VERTEX);
			}
			else if (shaderType == GL_GEOMETRY_SHADER)
			{
				LOG_ERROR("SHADER", "Failed to compile geometry Shader!\n", &error[0]);
				ErrorHandle::setErrorCode(GREET_ERROR_SHADER_GEOMETRY);
			}
			glDeleteShader(shader);
			return ShaderFactory::DefaultShader()->m_shaderID;
		}	
		glAttachShader(program, shader);
		glDeleteShader(shader);
		return 0;
	}

	GLuint Shader::getUniformLocation(const GLchar *name) const
	{
		return glGetUniformLocation(m_shaderID,name);
	}

	void Shader::setUniformBoolean(const GLchar *name, bool value) const
	{
		glUniform1f(getUniformLocation(name), value ? 1.0f : 0.0f);
	}

	void Shader::setUniform1f(const GLchar *name, float value) const
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar *name, int count, float* value) const
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar *name, int value) const
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const GLchar *name, int count, int* value) const
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform2f(const GLchar *name, const math::vec2 &value) const
	{
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}

	void Shader::setUniform3f(const GLchar *name, const math::vec3 &value) const
	{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::setUniform4f(const GLchar *name, const math::vec4 &value) const
	{
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniformMat3(const GLchar *name, const math::mat3 &value) const
	{
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, value.elements);
	}

	void Shader::setUniformMat4(const GLchar *name, const math::mat4 &value) const
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.elements);
	}

	void Shader::enable() const
	{
		glUseProgram(m_shaderID);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

	Shader* Shader::fromFile(const std::string& vertPath, const std::string& fragPath)
	{	
		std::string vertSourceString = utils::read_file(vertPath.c_str());
		std::string fragSourceString = utils::read_file(fragPath.c_str());
		return new Shader(vertSourceString,fragSourceString); 
	}


	Shader* Shader::fromFile(const std::string& geomPath, const std::string& vertPath, const std::string& fragPath)
	{	
		std::string vertSourceString = utils::read_file(vertPath.c_str());
		std::string fragSourceString = utils::read_file(fragPath.c_str());
		std::string geomSourceString = utils::read_file(geomPath.c_str());
		return new Shader(geomSourceString, vertSourceString,fragSourceString); 
	}

	Shader* Shader::fromSource(const std::string& vertSrc, const std::string& fragSrc)
	{
		return new Shader(vertSrc, fragSrc);
	}

	Shader* Shader::fromSource(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc)
	{
		return new Shader(vertSrc, fragSrc);
	}
}}