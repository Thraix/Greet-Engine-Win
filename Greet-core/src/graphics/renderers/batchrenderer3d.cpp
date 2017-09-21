#include "batchrenderer3d.h"

namespace Greet {

	void BatchRenderer3D::submit(const EntityModel* model)
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

	void BatchRenderer3D::render() const
	{
		glDepthRange(m_near, m_far);
		const mat4& viewMatrix = m_camera->getViewMatrix();
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

	vec3 BatchRenderer3D::getScreenCoordination(const vec3& coordinate, uint screenWidth, uint screenHeight)
	{
		vec3 point = getProjectionMatrix() * getCamera().getViewMatrix() * coordinate;
		vec3 p = vec3(point.x, point.y, point.z) / (fabs(point.z) * 2.0f) + 0.5f;
		p.x *= screenWidth;
		p.y = screenHeight - p.y * screenHeight;
		return p;
	}
}