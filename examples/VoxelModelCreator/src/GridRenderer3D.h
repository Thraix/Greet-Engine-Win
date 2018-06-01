#pragma once

#include <greet.h>
#include "Cube.h"

namespace vmc
{

	class GridRenderer3D : public Greet::Renderer3D
	{
	private:

		Greet::EntityModel* emodel;
		Greet::MaterialModel* mmodel;
		Greet::Material* material;
		Greet::Mesh* mesh;
		Greet::MeshData* meshdata;


		Greet::Shader lineShader;
		uint m_vao;
		uint m_vbo;
		uint m_ibo;
		uint* m_indices;
	public:

		GridRenderer3D(uint w, uint h, Greet::Camera* cam, float fov, float near, float far, Greet::Skybox* skybox);

		void UpdateShader();
		void Begin();
		void DrawCube(const Greet::Vec3& pos, const Greet::Vec3& size, uint color, bool culling);
		void Submit(const Cube& cube);
		void DrawLineCube(const Greet::Vec3& pos, const Greet::Vec3& size, const Greet::Vec4& color);
		void DrawLine(const Greet::Vec3& start, const Greet::Vec3& end, const Greet::Vec4& color);
	};
}