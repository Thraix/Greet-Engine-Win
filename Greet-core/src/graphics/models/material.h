#pragma once

#include <graphics/shaders/shader.h>
#include <graphics/textures/texture.h>

namespace Greet {

	class Material
	{
	private:
		Shader* m_shader;
		Texture* m_texture;
		float m_shineDamper = 10;
		float m_reflectivity = 1;

	public:
		Material(Shader* shader, Texture* texture);
		virtual ~Material();

		void bind() const;
		void unbind() const;
		void setShader(Shader* shader);
		Material* setReflectivity(float reflectivity);
		Material* setShineDamper(float shineDamper);

		inline float getReflectivity() const { return m_reflectivity; }
		inline float getShineDamper() const { return m_shineDamper; }
		inline const Shader& getShader() const { return *m_shader; }
		inline const Texture& getTexture() const { return *m_texture; }
		inline uint getTextureId() const { return m_texture == NULL ? 0 : m_texture->getTexId(); }
	private:
		void updateTexture();
	};

}