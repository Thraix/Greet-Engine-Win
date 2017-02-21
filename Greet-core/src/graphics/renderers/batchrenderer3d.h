#pragma once

#include <map>
#include <vector>
#include <graphics/models/entitymodel.h>
#include <graphics/models/camera.h>
#include <utils/objutils.h>
#include <graphics/textures/texturemanager.h>
#include <graphics/skybox.h>
#include <graphics/models/meshfactory.h>
#include <graphics/renderers/renderer3d.h>

namespace greet { namespace graphics {

	struct BatchRenderer3DMap
	{
		friend class BatchRenderer3D;
	private:
		const model::MaterialModel& m_material;
		std::vector<const model::EntityModel*> m_models;
		BatchRenderer3DMap(const model::MaterialModel& material) : m_material(material) {}
		void addEntity(const model::EntityModel* model) { m_models.push_back(model); };
	};

	class BatchRenderer3D : public Renderer3D
	{
	private:
		std::vector<BatchRenderer3DMap*> m_map;
	public:
		BatchRenderer3D(float width, float height, const model::Camera& camera, float fov, float near, float far, Skybox* skybox)
			: Renderer3D(width,height,camera,fov,near,far,skybox)
		{
			
		}

		void submit(const model::EntityModel* model) override;
		void render() const override;

		inline const math::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		inline const model::Camera& getCamera() const { return m_camera; }

		math::vec3 getScreenCoordination(const math::vec3& coordinate, uint screenWidth, uint screenHeight);

	};
}}