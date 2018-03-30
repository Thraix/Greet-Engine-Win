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
	public:
		GridRenderer3D(uint w, uint h, Greet::Camera* cam, float fov, float near, float far, Greet::Skybox* skybox)
			: Greet::Renderer3D(w,h,cam,fov,near,far, skybox)
		{
			meshdata = Greet::MeshFactory::Cube(0,0,0,1,1,1);
			mesh = new Greet::Mesh(meshdata);
			material = new Greet::Material(Greet::Shader::FromFile("res/shaders/3dshader.shader"), NULL);
			//material->AddUniform<uint>(Uniform1ui("color"));
			mmodel = new Greet::MaterialModel(mesh, *material);
			emodel = new Greet::EntityModel(*mmodel, 0, 0, 0, 1, 1, 1, 0, 0, 0);
		}
		
		void Submit(const Cube& cube) 
		{
			//material->GetUniform<uint>("color").SetValue(cube.color);
			material->SetColor(cube.color);
			emodel->SetPosition(cube.GetPosition());
			emodel->UpdateTransformation();
			Render(*emodel);
		}
	};
}