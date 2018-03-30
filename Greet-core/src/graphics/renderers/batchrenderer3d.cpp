#include "BatchRenderer3D.h"

namespace Greet {

	void BatchRenderer3D::Submit(const EntityModel* model)
	{
		for (BatchRenderer3DMap* map : m_map)
		{
			if (map->m_material == model->GetMaterialModel())
			{
				map->AddEntity(model);
				return;
			}
		}
		BatchRenderer3DMap* map = new BatchRenderer3DMap(model->GetMaterialModel());
		map->AddEntity(model);
		m_map.push_back(map);
	}

	void BatchRenderer3D::Render() const
	{
		GLCall(glDepthRange(m_near, m_far));
		const Mat4& viewMatrix = m_camera->GetViewMatrix();
		for (BatchRenderer3DMap* map : m_map)
		{
			map->m_material.GetMaterial().Bind();
			map->m_material.GetMaterial().GetShader().SetUniformMat4("projectionMatrix", m_projectionMatrix);
			map->m_material.GetMaterial().GetShader().SetUniformMat4("viewMatrix", viewMatrix);
			const Mesh& mesh = map->m_material.GetMesh();
			mesh.Bind();
			for (const EntityModel* model : map->m_models)
			{
				map->m_material.GetMaterial().GetShader().SetUniformMat4("transformationMatrix", model->GetTransformationMatrix());
				mesh.Render();
			}
			mesh.Unbind();
			map->m_material.GetMaterial().Unbind();
		}

	}

	Vec3 BatchRenderer3D::GetScreenCoordination(const Vec3& coordinate, uint screenWidth, uint screenHeight)
	{
		Vec4 point = (GetProjectionMatrix() * GetCamera().GetViewMatrix()) * coordinate;
		Vec3 p = Vec3(point.x, point.y, point.z) / (fabs(point.z) * 2.0f) + 0.5f;
		p.x *= screenWidth;
		p.y = screenHeight - p.y * screenHeight;
		return p;
	}

	void BatchRenderer3D::GetWorldCoordination(const Vec2& mousePos, Vec3* near, Vec3* direction)
	{
		if (near == NULL)
		{
			Log::Error("Near vector is NULL");
			return;
		}
		if (direction == NULL)
		{
			Log::Error("Direction vector is NULL");
			return;
		}
		Mat4 view = GetCamera().GetViewMatrix();
		Mat4 proj = GetProjectionMatrix();
		Vec4 nearRes = ~view * ~proj * Vec3(mousePos.x, mousePos.y, -1.0);
		*near = Vec3(nearRes)/nearRes.w;
		Vec4 farRes = ~view * ~proj * Vec3(mousePos.x, mousePos.y, 1.0);
		*direction = (Vec3(farRes) / farRes.w) - *near;
	}
}