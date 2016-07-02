#pragma once

#include <map>
#include <vector>
#include <graphics/models/entitymodel.h>
#include <graphics/models/camera.h>
#include <utils/objutils.h>
#include <graphics/textures/texturemanager.h>

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

		// Skybox
		model::Material* skyboxMaterial;
		model::MaterialModel* skybox;

	public:
		BatchRenderer3D(float width, float height, const model::Camera& camera, float fov, float near, float far)
			: m_renderDistance(far), m_projectionMatrix(math::mat4::projectionMatrix(width / height, fov, near, far)), m_camera(camera)
		{
			Shader* skyboxShader = new Shader("res/shaders/skybox.vert", "res/shaders/skybox.frag"); // TODO: CHANGE TO SHADERFACTORY SKYBOX SHADER
			model::Mesh* skyboxMesh = utils::loadObj("res/objs/cube.obj.gobj"); // TODO: CHANGE TO MESHFACTORY CUBE
			skyboxMesh->setClockwiseRender(true);
			skyboxMaterial = new model::Material(skyboxShader, TextureManager::get("skybox"));
			skybox = new model::MaterialModel(skyboxMesh, *skyboxMaterial);
		}

		virtual ~BatchRenderer3D()
		{
			delete skybox;
			delete skyboxMaterial;
		}

		void submit(const model::EntityModel* model);
		void begin();
		void flush() const;
		void end();
	private:
		void submitSkybox();

	};
}}