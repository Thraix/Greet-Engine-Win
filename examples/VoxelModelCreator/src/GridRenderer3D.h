#pragma once

#include <greet.h>
#include "Cube.h"

namespace vmc
{

	class GridRenderer3D : public Greet::Renderer3D
	{
	private:
		Greet::Shader* simpleShader;

		Greet::EntityModel* emodel;
		Greet::MaterialModel* mmodel;
		Greet::Material* material;
		Greet::Mesh* mesh;
		Greet::MeshData* meshdata;


		Greet::Shader* lineShader;
		uint m_vao;
		uint m_vbo;
		uint m_ibo;
		uint* m_indices;
	public:

		GridRenderer3D(uint w, uint h, Greet::Camera* cam, float fov, float near, float far, Greet::Skybox* skybox)
			: Greet::Renderer3D(w,h,cam,fov,near,far, skybox)
		{
			meshdata = Greet::MeshFactory::Cube(0.5f,0.5f,0.5f,1,1,1);
			mesh = new Greet::Mesh(meshdata);
			material = new Greet::Material(Greet::Shader::FromFile("res/shaders/3dshader.shader"), NULL);
			//material->AddUniform<uint>(Uniform1ui("color"));
			mmodel = new Greet::MaterialModel(mesh, *material);
			emodel = new Greet::EntityModel(*mmodel, 0, 0, 0, 1, 1, 1, 0, 0, 0);


			// For drawing lines...
			lineShader = Greet::Shader::FromFile("res/shaders/simple.shader");
			GLCall(glGenVertexArrays(1, &m_vao));
			GLCall(glGenBuffers(1, &m_vbo));

			GLCall(glBindVertexArray(m_vao));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

			GLCall(glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Greet::Vec3), NULL, GL_DYNAMIC_DRAW));
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Greet::Vec3), 0));

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

			m_indices = new uint[2]{ 0,1 };
			GLCall(glGenBuffers(1, &m_ibo));
			GLCall(glBindVertexArray(0));
		}

		void Begin()
		{
			Renderer3D::Begin();
			glLineWidth(3.0f);
		}
		
		void DrawCube(const Greet::Vec3& pos, const Greet::Vec3& size, uint color, bool culling)
		{
			material->SetColor(color);
			mesh->SetEnableCulling(false);
			emodel->SetScale(size);
			emodel->SetPosition(pos);
			emodel->SetRotation(Greet::Vec3(0, 0, 0));
			emodel->UpdateTransformation();
			Render(*emodel);
		}

		void Submit(const Cube& cube) 
		{
			//material->GetUniform<uint>("color").SetValue(cube.color);
			material->SetColor(cube.color);
			mesh->SetEnableCulling(true);
			emodel->SetScale(Greet::Vec3(1, 1, 1));
			emodel->SetPosition(cube.GetPosition());
			emodel->SetRotation(Greet::Vec3(0, 0, 0));
			emodel->UpdateTransformation();
			Render(*emodel);
		}

		void DrawLine(const Greet::Vec3& start, const Greet::Vec3& end, const Greet::Vec4& color)
		{
			using namespace Greet;
			lineShader->Enable();
			lineShader->SetUniformMat4("projectionMatrix", GetProjectionMatrix());
			lineShader->SetUniformMat4("viewMatrix", GetCamera().GetViewMatrix());
			lineShader->SetUniform4f("mat_color", color);

			Vec3* buffer = NULL;
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
			GLCall(buffer = (Vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

			buffer[0] = start;
			buffer[1] = end;

			GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

			GLCall(glBindVertexArray(m_vao));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(uint), m_indices, GL_DYNAMIC_DRAW));

			GLCall(glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL));

			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
			GLCall(glBindVertexArray(0));

			lineShader->Disable();
		}
	};
}