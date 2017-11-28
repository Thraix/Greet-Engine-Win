#include "material.h"

namespace Greet {

	Material::Material(Shader* shader, Texture* texture)
		: m_shader(shader), m_texture(texture)
	{
		UpdateTexture();
	}

	Material::~Material()
	{
		delete m_shader;
	}

	void Material::Bind() const
	{
		m_shader->Enable();
		m_shader->SetUniform1f("reflectivity", m_reflectivity);
		m_shader->SetUniform1f("shineDamper", m_shineDamper);
		//m_shader->setUniform3f("fogColor", Vec3(0.0,1.0,0.0));
		m_shader->SetUniform1f("shineDamper", m_shineDamper);
		if (m_texture != NULL)
			m_texture->Enable();
			
	}

	void Material::Unbind() const
	{
		if (m_texture != NULL)
			m_texture->Disable();
		m_shader->Disable();
	}

	void Material::SetShader(Shader* shader)
	{
		delete m_shader;
		m_shader = shader;
		UpdateTexture();
	}

	void Material::UpdateTexture()
	{
		if (m_texture == NULL)
		{
			m_shader->Enable();
			m_shader->SetUniformBoolean("hasTexture", false);
			m_shader->Disable();
		}
	}

	Material* Material::SetReflectivity(float reflectivity) 
	{
		m_reflectivity = reflectivity;
		return this;
	}

	Material* Material::SetShineDamper(float shineDamper)
	{
		m_shineDamper = shineDamper;
		return this;
	}
}