#include "shader.h"
#include "shaderfactory.h"
namespace greet { namespace graphics {
	Shader::Shader(const char *vertPath, const char *fragPath)
		:m_name(vertPath), m_vertPath(vertPath), m_fragPath(fragPath)
	{

		std::string vertSourceString = utils::read_file(m_vertPath);
		std::string fragSourceString = utils::read_file(m_fragPath);
		m_vertSrc = vertSourceString.c_str();
		m_fragSrc = fragSourceString.c_str();

		m_shaderID = load();
	}

	Shader::Shader(const char *name, const char *vertSrc, const char *fragSrc)
		: m_name(name), m_vertSrc(vertSrc), m_fragSrc(fragSrc)
	{
		m_shaderID = load();
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex, 1, &m_vertSrc, NULL);
		glCompileShader(vertex);

		GLint resultVert;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &resultVert);
		if (resultVert == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			LOG_ERROR("SHADER","Failed to compile vertex Shader!\n", &error[0]);
			glDeleteShader(vertex);
			return ShaderFactory::DefaultShader()->m_shaderID;
		}

		glShaderSource(fragment, 1, &m_fragSrc, NULL);
		glCompileShader(fragment);

		GLint resultFrag;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &resultFrag);
		if (resultFrag == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			LOG_ERROR("SHADER","Failed to compile fragment Shader!\n", &error[0]);
			for (char c : error)
			{
				std::cout << c;
			}
			std::cout << std::endl;
			std::cout << &error << std::endl;
			glDeleteShader(fragment);
			return ShaderFactory::DefaultShader()->m_shaderID;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
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

	Shader* Shader::fromFile(const char* vertPath, const char* fragPath)
	{
		return new Shader(vertPath,fragPath); 
	}
	Shader* Shader::fromSource(const char* vertSrc, const char* fragSrc)
	{
		return new Shader(vertSrc,vertSrc, fragSrc);
	}

	Shader* Shader::fromSource(const char* name, const char* vertSrc, const char* fragSrc)
	{
		return new Shader(name, vertSrc, fragSrc);
	}
}}