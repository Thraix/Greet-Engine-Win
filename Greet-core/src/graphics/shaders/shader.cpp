#include "Shader.h"

#include "ShaderFactory.h"
namespace Greet {

	Shader::Shader(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc)
	{
		m_shaderID = Load(geomSrc, vertSrc, fragSrc,true);
	}

	Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
	{
		m_shaderID = Load(vertSrc,fragSrc);
	}

	GLuint Shader::Load(const std::string& vertSrc, const std::string& fragSrc)
	{
		return Load("", vertSrc, fragSrc, false);
	}

	GLuint Shader::Load(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc, bool hasGeometry)
	{
		GLuint program = glCreateProgram();

		uint shader = AttachShader(program, vertSrc, GL_VERTEX_SHADER);
		if (shader != 0)
			return shader;
		shader = AttachShader(program, fragSrc, GL_FRAGMENT_SHADER);
		if (shader != 0)
			return shader;
		if (hasGeometry)
		{
			AttachShader(program, geomSrc, GL_GEOMETRY_SHADER);
			if (shader != 0)
				return shader;
		}
		glLinkProgram(program);
		glValidateProgram(program);


		return program;
	}

	GLuint Shader::AttachShader(const GLuint program, const std::string& shaderSrc, const GLuint shaderType)
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
			if (shaderType == GL_FRAGMENT_SHADER)
			{
				Log::Error("Failed to compile fragment Shader!\n", &error[0]);
				ErrorHandle::SetErrorCode(GREET_ERROR_SHADER_FRAGMENT);
			}
			else if (shaderType == GL_VERTEX_SHADER)
			{
				Log::Error("Failed to compile vertex Shader!\n", &error[0]);
				ErrorHandle::SetErrorCode(GREET_ERROR_SHADER_VERTEX);
			}
			else if (shaderType == GL_GEOMETRY_SHADER)
			{
				Log::Error("Failed to compile geometry Shader!\n", &error[0]);
				ErrorHandle::SetErrorCode(GREET_ERROR_SHADER_GEOMETRY);
			}
			glDeleteShader(shader);
			return ShaderFactory::DefaultShader()->m_shaderID;
		}	
		glAttachShader(program, shader);
		glDeleteShader(shader);
		return 0;
	}

	void Shader::BindAttributeOutput(uint attachmentId, const std::string& name)
	{
		glBindFragDataLocation(m_shaderID,attachmentId,name.c_str());
	}

	GLuint Shader::GetUniformLocation(const GLchar *name) const
	{
		return glGetUniformLocation(m_shaderID,name);
	}

	void Shader::SetUniformBoolean(const GLchar *name, bool value) const
	{
		glUniform1f(GetUniformLocation(name), value ? 1.0f : 0.0f);
	}

	void Shader::SetUniform1f(const GLchar *name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar *name, int count, float* value) const
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar *name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar *name, int count, int* value) const
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar *name, const Vec2 &value) const
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetUniform3f(const GLchar *name, const Vec3 &value) const
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetUniform4f(const GLchar *name, const vec4 &value) const
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniformMat3(const GLchar *name, const Mat3 &value) const
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, value.elements);
	}

	void Shader::SetUniformMat4(const GLchar *name, const Mat4 &value) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value.elements);
	}

	void Shader::Enable() const
	{
		glUseProgram(m_shaderID);
	}

	void Shader::Disable()
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

	Shader* Shader::FromFile(const std::string& vertPath, const std::string& fragPath)
	{	
		std::string vertSourceString = FileUtils::read_file(vertPath.c_str());
		std::string fragSourceString = FileUtils::read_file(fragPath.c_str());
		return new Shader(vertSourceString,fragSourceString); 
	}


	Shader* Shader::FromFile(const std::string& geomPath, const std::string& vertPath, const std::string& fragPath)
	{	
		std::string vertSourceString = FileUtils::read_file(vertPath.c_str());
		std::string fragSourceString = FileUtils::read_file(fragPath.c_str());
		std::string geomSourceString = FileUtils::read_file(geomPath.c_str());
		return new Shader(geomSourceString, vertSourceString,fragSourceString); 
	}

	Shader* Shader::FromSource(const std::string& vertSrc, const std::string& fragSrc)
	{
		return new Shader(vertSrc, fragSrc);
	}

	Shader* Shader::FromSource(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc)
	{
		return new Shader(vertSrc, fragSrc);
	}
}