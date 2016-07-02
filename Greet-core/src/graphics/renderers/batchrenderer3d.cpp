#include "batchrenderer3d.h"

namespace greet { namespace graphics {
	using namespace model;



	void BatchRenderer3D::submit(const model::EntityModel* model)
	{
		for (BatchRenderer3DMap* map : m_map)
		{
			if (map->m_material == model->getMaterialModel())
			{
				map->addEntity(model);
				return;
			}
		}
		BatchRenderer3DMap* map = new BatchRenderer3DMap(model->getMaterialModel());
		map->addEntity(model);
		m_map.push_back(map);
	}

	void BatchRenderer3D::submitSkybox()
	{
		skybox->getMaterial().bind();
		skybox->getMaterial().getShader().setUniformMat4("transformationMatrix", math::mat4::scale(math::vec3(m_renderDistance, m_renderDistance, m_renderDistance)));
		skybox->getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
		skybox->getMaterial().getShader().setUniformMat4("viewMatrix", math::mat4::viewMatrix(math::vec3(0, 0, 0), m_camera.getRotationVector()));
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		skybox->getMesh().bind();
		skybox->getMesh().render();
		skybox->getMesh().unbind();
		glDisable(GL_CULL_FACE);
		skybox->getMaterial().unbind();
	}

	void BatchRenderer3D::begin()
	{
		submitSkybox();
	}

	void BatchRenderer3D::flush() const
	{
		glEnable(GL_CULL_FACE);
		const math::mat4& viewMatrix = math::mat4::viewMatrix(m_camera.position, math::vec3(m_camera.pitch, m_camera.yaw, m_camera.roll));
		for (BatchRenderer3DMap* map : m_map)
		{
			map->m_material.getMaterial().bind();
			map->m_material.getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
			map->m_material.getMaterial().getShader().setUniformMat4("viewMatrix", viewMatrix);
			const Mesh& mesh = map->m_material.getMesh();
			glFrontFace(mesh.isClockwiseRender() ? GL_CW : GL_CCW);
			mesh.bind();
			for (const EntityModel* model : map->m_models)
			{
				map->m_material.getMaterial().getShader().setUniformMat4("transformationMatrix", model->getTransformationMatrix());
				mesh.render();
			}
			mesh.unbind();
			map->m_material.getMaterial().unbind();
		}
		glDisable(GL_CULL_FACE);
	}

	void BatchRenderer3D::end()
	{
		
	}
} }