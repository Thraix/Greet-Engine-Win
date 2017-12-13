#include "Renderer3D.h"

namespace Greet{
	void Renderer3D::Render(const Mesh& mesh) const
	{
		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glFrontFace(mesh.IsClockwiseRender() ? GL_CW : GL_CCW));
		mesh.Bind();
		mesh.Render();
		mesh.Unbind();
		GLCall(glDisable(GL_CULL_FACE));
	}

	void Renderer3D::Render(const MaterialModel& model) const
	{
		Render(model.GetMesh());
	}

	void Renderer3D::RenderSkybox() const
	{
		m_skybox->Render(m_projectionMatrix, *m_camera);
	}

	void Renderer3D::Render(const EntityModel& model) const
	{
		const MaterialModel& materialModel = model.GetMaterialModel();
		materialModel.GetMaterial().Bind();
		materialModel.GetMaterial().GetShader().SetUniformMat4("transformationMatrix", model.GetTransformationMatrix());
		materialModel.GetMaterial().GetShader().SetUniformMat4("projectionMatrix", m_projectionMatrix);
		materialModel.GetMaterial().GetShader().SetUniformMat4("viewMatrix", m_camera->GetViewMatrix());
		Render(materialModel.GetMesh());
		materialModel.GetMaterial().Unbind();
	}

	void Renderer3D::Update(float timeElapsed)
	{
		m_camera->Update(timeElapsed);
	}
}