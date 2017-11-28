#pragma once

#include <graphics/shaders/Shader.h>
#include <graphics/textures/Texture.h>

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

		void Bind() const;
		void Unbind() const;
		void SetShader(Shader* shader);
		Material* SetReflectivity(float reflectivity);
		Material* SetShineDamper(float shineDamper);

		inline float GetReflectivity() const { return m_reflectivity; }
		inline float GetShineDamper() const { return m_shineDamper; }
		inline const Shader& GetShader() const { return *m_shader; }
		inline const Texture& GetTexture() const { return *m_texture; }
		inline uint GetTextureId() const { return m_texture == NULL ? 0 : m_texture->GetTexId(); }
	private:
		void UpdateTexture();
	};

}