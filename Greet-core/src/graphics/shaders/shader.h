#pragma once

#include <logging/logger.h>
#include <internal/greetgl.h>
#include <math/maths.h>
#include <utils/fileutils.h>
#include <iostream>
#include <vector>
#include <utils/errorhandler.h>

namespace greet { namespace graphics {
	class Shader
	{
	private:
		std::string m_name;
		std::string m_vertPath;
		std::string m_fragPath;
		std::string m_vertSrc;
		std::string m_fragSrc;
		GLuint m_shaderID;

	private:
		GLuint load();
		GLuint getUniformLocation(const GLchar *name) const;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		Shader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);

		~Shader();
		void enable() const;
		
		static void disable();
		void setUniformBoolean(const GLchar *name, bool value) const;
		void setUniform1f(const GLchar *name, float value) const;
		void setUniform1fv(const GLchar *name, int count, float* value) const;
		void setUniform1i(const GLchar *name, int value) const;
		void setUniform1iv(const GLchar *name, int count, int* value) const;
		void setUniform2f(const GLchar *name, const math::vec2 &value) const;
		void setUniform3f(const GLchar *name, const math::vec3 &value) const;
		void setUniform4f(const GLchar *name, const math::vec4 &value) const;
		void setUniformMat3(const GLchar *name, const math::mat3 &value) const;
		void setUniformMat4(const GLchar *name, const math::mat4 &value) const;
	public:
		static Shader* fromFile(const char* vertPath, const char* fragPath);
		static Shader* fromSource(const char* vertSrc, const char* fragSrc);
		static Shader* fromSource(const char* name, const char* vertSrc, const char* fragSrc);
	};

}}
