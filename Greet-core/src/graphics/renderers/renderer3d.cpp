#include "renderer3d.h"

namespace greet{ namespace graphics{
	using namespace model;
	void Renderer3D::submit(const Mesh& mesh) const
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(mesh.isClockwiseRender() ? GL_CW : GL_CCW);
		mesh.bind();
		mesh.render();
		mesh.unbind();
		glDisable(GL_CULL_FACE);
	}

	void Renderer3D::submit(const MaterialModel& model) const
	{
		submit(model.getMesh());
	}

	void Renderer3D::submitSkybox(const model::MaterialModel& model) const
	{
		model.getMaterial().bind();
		model.getMaterial().getShader().setUniformMat4("transformationMatrix", math::mat4::scale(math::vec3(m_renderDistance, m_renderDistance, m_renderDistance)));
		model.getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
		model.getMaterial().getShader().setUniformMat4("viewMatrix", math::mat4::viewMatrix(math::vec3(0, 0, 0), m_camera.getRotationVector()));
		submit(model.getMesh());
		model.getMaterial().unbind();
	}

	void Renderer3D::submit(const EntityModel& model) const
	{
		const MaterialModel& materialModel = model.getMaterialModel();
		materialModel.getMaterial().bind();
		materialModel.getMaterial().getShader().setUniformMat4("transformationMatrix", model.getTransformationMatrix());
		materialModel.getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
		materialModel.getMaterial().getShader().setUniformMat4("viewMatrix", math::mat4::viewMatrix(m_camera.position, m_camera.getRotationVector()));
		submit(materialModel.getMesh());
		materialModel.getMaterial().unbind();
	}
}}