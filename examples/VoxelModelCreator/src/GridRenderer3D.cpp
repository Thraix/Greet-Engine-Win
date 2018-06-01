#include "GridRenderer3D.h"

namespace vmc
{
	using namespace Greet;

	GridRenderer3D::GridRenderer3D(uint w, uint h, Camera* cam, float fov, float near, float far, Skybox* skybox)
		: Renderer3D(w, h, cam, fov, near, far, skybox), lineShader(Shader::FromFile("res/shaders/simple.shader"))
	{
		meshdata = MeshFactory::Cube2(0.5f, 0.5f, 0.5f, 1, 1, 1);
		Vec2* texCoords = new Vec2[6 * 4];
		for (int i = 0;i < 6;i++)
		{
			texCoords[i * 4 + 0] = Vec2(0, 0);
			texCoords[i * 4 + 1] = Vec2(1, 0);
			texCoords[i * 4 + 2] = Vec2(1, 1);
			texCoords[i * 4 + 3] = Vec2(0, 1);
		}

		meshdata->AddAttribute(new AttributeData(ATTRIBUTE_TEXCOORD, (float*)texCoords));
		mesh = new Mesh(meshdata);
		material = new Material(Shader::FromFile("res/shaders/voxel.shader"), NULL);
		//material->AddUniform<uint>(Uniform1ui("color"));
		mmodel = new MaterialModel(mesh, *material);
		emodel = new EntityModel(*mmodel, 0, 0, 0, 1, 1, 1, 0, 0, 0);

		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glGenBuffers(1, &m_vbo));

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

		GLCall(glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vec3), NULL, GL_DYNAMIC_DRAW));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		m_indices = new uint[2]{ 0,1 };
		GLCall(glGenBuffers(1, &m_ibo));
		GLCall(glBindVertexArray(0));
	}
	void GridRenderer3D::UpdateShader()
	{
		material->SetShader(Shader::FromFile("res/shaders/voxel.shader"));
	}

	void GridRenderer3D::Begin()
	{
		Renderer3D::Begin();
		glLineWidth(1.0f);
	}

	void GridRenderer3D::DrawCube(const Vec3& pos, const Vec3& size, uint color, bool culling)
	{
		material->SetColor(color);
		mesh->SetEnableCulling(false);
		emodel->SetScale(size);
		emodel->SetPosition(pos);
		emodel->SetRotation(Vec3(0, 0, 0));
		emodel->UpdateTransformation();
		Render(*emodel);
	}

	void GridRenderer3D::Submit(const Cube& cube)
	{
		//material->GetUniform<uint>("color").SetValue(cube.color);
		material->SetColor(cube.color);
		mesh->SetEnableCulling(true);
		emodel->SetScale(Vec3(1, 1, 1));
		emodel->SetPosition(cube.GetPosition());
		emodel->SetRotation(Vec3(0, 0, 0));
		emodel->UpdateTransformation();
		Render(*emodel);
	}

	void GridRenderer3D::DrawLineCube(const Vec3& pos, const Vec3& size, const Vec4& color)
	{
		DrawLine(Vec3(pos.x, pos.y, pos.z), Vec3(pos.x + size.x, pos.y, pos.z), color);
		DrawLine(Vec3(pos.x, pos.y + size.y, pos.z), Vec3(pos.x + size.x, pos.y + size.y, pos.z), color);
		DrawLine(Vec3(pos.x, pos.y + size.y, pos.z + size.z), Vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), color);
		DrawLine(Vec3(pos.x, pos.y, pos.z + size.z), Vec3(pos.x + size.x, pos.y, pos.z + size.z), color);

		DrawLine(Vec3(pos.x, pos.y, pos.z), Vec3(pos.x, pos.y+size.y, pos.z), color);
		DrawLine(Vec3(pos.x + size.x, pos.y, pos.z), Vec3(pos.x + size.x, pos.y + size.y, pos.z), color);
		DrawLine(Vec3(pos.x + size.x, pos.y, pos.z + size.z), Vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), color);
		DrawLine(Vec3(pos.x, pos.y, pos.z + size.z), Vec3(pos.x, pos.y + size.y, pos.z + size.z), color);

		DrawLine(Vec3(pos.x, pos.y, pos.z), Vec3(pos.x, pos.y, pos.z+size.z), color);
		DrawLine(Vec3(pos.x, pos.y + size.y, pos.z), Vec3(pos.x, pos.y + size.y, pos.z+size.z), color);
		DrawLine(Vec3(pos.x + size.x, pos.y + size.y, pos.z), Vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), color);
		DrawLine(Vec3(pos.x + size.x, pos.y, pos.z), Vec3(pos.x + size.x, pos.y, pos.z + size.z), color);
	}

	void GridRenderer3D::DrawLine(const Vec3& start, const Vec3& end, const Vec4& color)
	{
		lineShader.Enable();
		lineShader.SetUniformMat4("projectionMatrix", GetProjectionMatrix());
		lineShader.SetUniformMat4("viewMatrix", GetCamera().GetViewMatrix());
		lineShader.SetUniform4f("mat_color", color);

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

		lineShader.Disable();
	}
}