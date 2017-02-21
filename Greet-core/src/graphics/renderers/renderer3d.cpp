#include "renderer3d.h"

namespace greet{ namespace graphics{
	using namespace model;
	void Renderer3D::render(const Mesh& mesh) const
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(mesh.isClockwiseRender() ? GL_CW : GL_CCW);
		mesh.bind();
		mesh.render();
		mesh.unbind();
		glDisable(GL_CULL_FACE);
	}

	void Renderer3D::render(const MaterialModel& model) const
	{
		render(model.getMesh());
	}

	void Renderer3D::renderSkybox() const
	{
		m_skybox->render(m_projectionMatrix, m_camera);
	}

	void Renderer3D::render(const EntityModel& model) const
	{
		const MaterialModel& materialModel = model.getMaterialModel();
		materialModel.getMaterial().bind();
		materialModel.getMaterial().getShader().setUniformMat4("transformationMatrix", model.getTransformationMatrix());
		materialModel.getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
		materialModel.getMaterial().getShader().setUniformMat4("viewMatrix", math::mat4::viewMatrix(m_camera.position, m_camera.getRotationVector()));
		render(materialModel.getMesh());
		materialModel.getMaterial().unbind();
	}
}}