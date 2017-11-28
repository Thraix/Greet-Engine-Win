#include "Skybox.h"

namespace Greet {
	
	Skybox::Skybox(CubeMap* cubemap) : m_map(cubemap) 
	{
		m_shader = ShaderFactory::SkyboxShader();
		MeshData* data = MeshFactory::Cube(0,0,0,1,1,1);
		m_mesh = new Mesh(data);
		m_mesh->SetClockwiseRender(true);
		delete data;
	}

	Skybox::~Skybox()
	{
		delete m_shader;
		delete m_mesh;
	}

	void Skybox::Render(const Mat4& projectionMatrix, const Camera& camera) const
	{
		m_shader->Enable();
		m_shader->SetUniformMat4("projectionMatrix", projectionMatrix);
		m_shader->SetUniformMat4("viewMatrix", Mat4::ViewMatrix(Vec3(0, 0, 0), camera.GetRotationVector()));
		glActiveTexture(GL_TEXTURE0);
		m_map->Enable();
		glDisable(GL_DEPTH_BUFFER);
		glDepthMask(GL_FALSE);
		glFrontFace(GL_CCW);
		m_mesh->Bind();
		m_mesh->Render();
		m_mesh->Unbind();
		glEnable(GL_DEPTH_BUFFER);
		glDepthMask(GL_TRUE);
		m_map->Disable();
		m_shader->Disable();
	}
}