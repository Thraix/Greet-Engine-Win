#pragma once

#include <logging/log.h>
#include <internal/Greetgl.h>
#include <math/maths.h>
#include <utils/fileutils.h>
#include <iostream>
#include <vector>
#include <utils/errorhandler.h>

namespace Greet {
	class Shader
	{
	private:
		GLuint m_shaderID;

	private:
		GLuint load(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc, bool hasGeometry);
		GLuint load(const std::string& vertSrc, const std::string& fragSrc);
		GLuint attachShader(const GLuint program, const std::string& shaderSrc, const GLuint shaderType);
		GLuint getUniformLocation(const GLchar *name) const;

		Shader(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc);
		Shader(const std::string& vertSrc, const std::string& fragSrc);
	public:

		virtual ~Shader();
		void enable() const;
		static void disable();
		void bindAttributeOutput(uint attachmentId, const std::string& name);

		void setUniformBoolean(const GLchar *name, bool value) const;
		void setUniform1f(const GLchar *name, float value) const;
		void setUniform1fv(const GLchar *name, int count, float* value) const;
		void setUniform1i(const GLchar *name, int value) const;
		void setUniform1iv(const GLchar *name, int count, int* value) const;
		void setUniform2f(const GLchar *name, const vec2 &value) const;
		void setUniform3f(const GLchar *name, const vec3 &value) const;
		void setUniform4f(const GLchar *name, const vec4 &value) const;
		void setUniformMat3(const GLchar *name, const mat3 &value) const;
		void setUniformMat4(const GLchar *name, const mat4 &value) const;
	public:
		static Shader* fromFile(const std::string& vertPath, const std::string& fragPath);
		static Shader* fromFile(const std::string& geomPath, const std::string& vertPath, const std::string& fragPath);
		static Shader* fromSource(const std::string& vertSrc, const std::string& fragSrc);
		static Shader* fromSource(const std::string& geomSrc, const std::string& vertSrc, const std::string& fragSrc);
	};

}
