#include "skybox.h"

namespace Greet {
	
	Skybox::Skybox(CubeMap* cubemap) : m_map(cubemap) 
	{
		m_shader = ShaderFactory::SkyboxShader();
		MeshData* data = MeshFactory::cube(0,0,0,1,1,1);
		m_mesh = new Mesh(data);
		m_mesh->setClockwiseRender(true);
		delete data;
	}

	Skybox::~Skybox()
	{
		delete m_shader;
		delete m_mesh;
	}

	void Skybox::render(const mat4& projectionMatrix, const Camera& camera) const
	{
		m_shader->enable();
		m_shader->setUniformMat4("projectionMatrix", projectionMatrix);
		m_shader->setUniformMat4("viewMatrix", mat4::viewMatrix(vec3(0, 0, 0), camera.getRotationVector()));
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
}