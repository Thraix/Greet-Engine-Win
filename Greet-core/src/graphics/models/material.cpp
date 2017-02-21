#include "material.h"

namespace greet { namespace model{

	using namespace graphics;

	Material::Material(Shader* shader, Texture* texture)
		: m_shader(shader), m_texture(texture)
	{
		updateTexture();
	}

	Material::~Material()
	{
		delete m_shader;
	}

	void Material::bind() const
	{
		m_shader->enable();
		m_shader->setUniform1f("reflectivity", m_reflectivity);
		m_shader->setUniform1f("shineDamper", m_shineDamper);
		m_shader->setUniform3f("fogColor", math::vec3(0.2,0.2,0.2));
		m_shader->setUniform1f("shineDamper", m_shineDamper);
		if (m_texture != NULL)
			m_texture->enable();
			
	}

	void Material::unbind() const
	{
		if (m_texture != NULL)
			m_texture->disable();
		m_shader->disable();
	}

	void Material::setShader(Shader* shader)
	{
		delete m_shader;
		m_shader = shader;
		updateTexture();
	}

	void Material::updateTexture()
	{
		if (m_texture == NULL)
		{
			m_shader->enable();
			m_shader->setUniformBoolean("hasTexture", false);
			m_shader->disable();
		}
	}

	Material* Material::setReflectivity(float reflectivity) 
	{
		m_reflectivity = reflectivity;
		return this;
	}

	Material* Material::setShineDamper(float shineDamper)
	{
		m_shineDamper = shineDamper;
		return this;
	}
}}