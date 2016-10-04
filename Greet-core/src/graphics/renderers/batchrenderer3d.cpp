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
		m_skyboxShader->enable();
		//m_skyboxShader->setUniformMat4("transformationMatrix", math::mat4::scale(math::vec3(m_renderDistance,m_renderDistance,m_renderDistance)));
		m_skyboxShader->setUniformMat4("projectionMatrix", m_projectionMatrix);
		m_skyboxShader->setUniformMat4("viewMatrix", math::mat4::viewMatrix(math::vec3(0,0,0),m_camera.getRotationVector()));
		glActiveTexture(GL_TEXTURE0);
		m_skybox->enable();
		glDisable(GL_DEPTH_BUFFER);		
		glDepthMask(GL_FALSE);
		glFrontFace(m_skyboxMesh->isClockwiseRender() ? GL_CW : GL_CCW);
		m_skyboxMesh->bind();
		m_skyboxMesh->render();
		m_skyboxMesh->unbind();
		glEnable(GL_DEPTH_BUFFER);		
		glDepthMask(GL_TRUE);
		
		m_skyboxShader->disable();
		m_skybox->disable();
	}

	void BatchRenderer3D::begin()
	{
		submitSkybox();
	}

	void BatchRenderer3D::flush() const
	{
		//glDepthRange(m_near, m_far);
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