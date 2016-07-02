#pragma once

#include <graphics/shaders/shader.h>
#include <graphics/textures/texture.h>

namespace greet { namespace model{

	class Material
	{
	private:
		graphics::Shader* m_shader;
		graphics::Texture* m_texture;
		float m_shineDamper = 10;
		float m_reflectivity = 1;

	public:
		Material(graphics::Shader* shader, graphics::Texture* texture);
		virtual ~Material();

		void bind() const;
		void unbind() const;
		void setShader(graphics::Shader* shader);
		Material* setReflectivity(float reflectivity);
		Material* setShineDamper(float shineDamper);

		inline float getReflectivity() const { return m_reflectivity; }
		inline float getShineDamper() const { return m_shineDamper; }
		inline const graphics::Shader& getShader() const { return *m_shader; }
		inline const graphics::Texture& getTexture() const { return *m_texture; }
		inline const graphics::Texture& getTextureId() const { return m_texture == NULL ? 0 : m_texture->getTexID(); }
	private:
		void updateTexture();
	};

}}