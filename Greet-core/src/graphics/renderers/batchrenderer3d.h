#pragma once

#include <map>
#include <vector>
#include <graphics/models/entitymodel.h>
#include <graphics/models/camera.h>
#include <utils/objutils.h>
#include <graphics/textures/texturemanager.h>
#include <graphics/skybox.h>
#include <graphics/models/meshfactory.h>

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

	class BatchRenderer3D
	{
	private:
		math::mat4 m_projectionMatrix;
		const model::Camera& m_camera;
		float m_renderDistance;
		std::vector<BatchRenderer3DMap*> m_map;
		float m_near;
		float m_far;

		// Skybox
		Skybox* m_skybox;
	public:
		BatchRenderer3D(float width, float height, const model::Camera& camera, float fov, float near, float far, Skybox* skybox)
			: m_renderDistance(far), m_projectionMatrix(math::mat4::projectionMatrix(width / height, fov, near, far)), m_camera(camera), m_skybox(skybox),m_near(near),m_far(far)
		{
			
		}

		virtual ~BatchRenderer3D()
		{
			
			delete m_skybox;
		}

		void submit(const model::EntityModel* model);
		void begin();
		void flush() const;
		void end();

		inline const math::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		inline const model::Camera& getCamera() const { return m_camera; }

		math::vec3 getScreenCoordination(const math::vec3& coordinate, uint screenWidth, uint screenHeight);

	private:
		void submitSkybox();

	};
}}