#include "skybox.h"

namespace greet { namespace graphics {
	
	Skybox::Skybox(CubeMap* cubemap) : m_map(cubemap) 
	{
		m_shader = ShaderFactory::SkyboxShader();
		m_mesh = model::MeshFactory::cube(0,0,0,1,1,1);
		m_mesh->setClockwiseRender(true);
	}

	Skybox::~Skybox()
	{
		delete m_shader;
		delete m_mesh;
	}

	void Skybox::render(const math::mat4& projectionMatrix, const model::Camera& camera) const
	{
		m_shader->enable();
		m_shader->setUniformMat4("projectionMatrix", projectionMatrix);
		m_shader->setUniformMat4("viewMatrix", math::mat4::viewMatrix(math::vec3(0, 0, 0), camera.getRotationVector()));
		glActiveTexture(GL_TEXTURE0);
		m_map->enable();
		glDisable(GL_DEPTH_BUFFER);
		glDepthMask(GL_FALSE);
		glFrontFace(GL_CCW);
		m_mesh->bind();
		m_mesh->render();
		m_mesh->unbind();
		glEnable(GL_DEPTH_BUFFER);
		glDepthMask(GL_TRUE);
		m_map->disable();
		m_shader->disable();
	}
}}