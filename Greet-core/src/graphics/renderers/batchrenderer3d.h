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

namespace Greet {

	struct BatchRenderer3DMap
	{
		friend class BatchRenderer3D;
	private:
		const MaterialModel& m_material;
		std::vector<const EntityModel*> m_models;
		BatchRenderer3DMap(const MaterialModel& material) : m_material(material) {}
		void addEntity(const EntityModel* model) { m_models.push_back(model); };
	};

	class BatchRenderer3D : public Renderer3D
	{
	private:
		std::vector<BatchRenderer3DMap*> m_map;
	public:
		BatchRenderer3D(float width, float height, Camera* camera, float fov, float near, float far, Skybox* skybox)
			: Renderer3D(width,height,camera,fov,near,far,skybox)
		{
			
		}

		void submit(const EntityModel* model) override;
		void render() const override;

		inline const mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		inline const Camera& getCamera() const { return *m_camera; }

		vec3 getScreenCoordination(const vec3& coordinate, uint screenWidth, uint screenHeight);

	};
}