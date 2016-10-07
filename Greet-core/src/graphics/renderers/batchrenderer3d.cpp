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
		m_skybox->render(m_projectionMatrix,m_camera);
	}

	void BatchRenderer3D::begin()
	{
		submitSkybox();
	}

	void BatchRenderer3D::flush() const
	{
		glDepthRange(m_near, m_far);
		const math::mat4& viewMatrix = math::mat4::viewMatrix(m_camera.position, math::vec3(m_camera.pitch, m_camera.yaw, m_camera.roll));
		for (BatchRenderer3DMap* map : m_map)
		{
			map->m_material.getMaterial().bind();
			map->m_material.getMaterial().getShader().setUniformMat4("projectionMatrix", m_projectionMatrix);
			map->m_material.getMaterial().getShader().setUniformMat4("viewMatrix", viewMatrix);
			const Mesh& mesh = map->m_material.getMesh();
			mesh.bind();
			for (const EntityModel* model : map->m_models)
			{
				map->m_material.getMaterial().getShader().setUniformMat4("transformationMatrix", model->getTransformationMatrix());
				mesh.render();
			}
			mesh.unbind();
			map->m_material.getMaterial().unbind();
		}
	}

	void BatchRenderer3D::end()
	{
		
	}
} }