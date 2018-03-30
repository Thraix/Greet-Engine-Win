#pragma once

#include <map>
#include <vector>
#include <graphics/models/EntityModel.h>
#include <graphics/models/Camera.h>
#include <utils/ObjUtils.h>
#include <graphics/textures/TextureManager.h>
#include <graphics/Skybox.h>
#include <graphics/models/MeshFactory.h>
#include <graphics/renderers/Renderer3D.h>

namespace Greet {

	struct BatchRenderer3DMap
	{
		friend class BatchRenderer3D;
	private:
		const MaterialModel& m_material;
		std::vector<const EntityModel*> m_models;
		BatchRenderer3DMap(const MaterialModel& material) : m_material(material) {}
		void AddEntity(const EntityModel* model) { m_models.push_back(model); };
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

		void Submit(const EntityModel* model) override;
		void Render() const override;

		inline const Mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		inline const Camera& GetCamera() const { return *m_camera; }

		Vec3 GetScreenCoordination(const Vec3& coordinate, uint screenWidth, uint screenHeight);
		void GetWorldCoordination(const Vec2& mousePos, Vec3* near, Vec3* direction);
	};
}