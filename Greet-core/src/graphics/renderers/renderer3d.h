#pragma once

#include <vector>
#include <internal/GreetGL.h>
#include <math/Maths.h>
#include <graphics/fonts/Font.h>
#include <logging/Log.h>
#include <graphics/models/EntityModel.h>
#include <graphics/models/Camera.h>
#include <graphics/Skybox.h>


namespace Greet{

	class Renderer3D
	{

	protected:
		Mat4 m_projectionMatrix;
		Camera* m_camera;
		float m_renderDistance;
		float m_near;
		float m_far;
		Skybox* m_skybox;


	public:
		Renderer3D(float width, float height, Camera* camera, float fov, float near, float far, Skybox* skybox)
			: m_projectionMatrix(Mat4::ProjectionMatrix(width/height, fov, near, far)), m_camera(camera), m_skybox(skybox), m_renderDistance(far), m_near(near), m_far(far)
		{
			
		}
		virtual ~Renderer3D() 
		{
			delete m_skybox;
		}

		virtual void Render(const EntityModel& model) const;
		virtual void Render(const Mesh& model) const;
		virtual void Render(const MaterialModel& model) const;

		virtual void Update(float timeElapsed);

		virtual void Submit(const EntityModel* model) {};

		virtual void Begin() {
			RenderSkybox();
		};
		virtual void Render() const {};
		virtual void End() {};
	private:
		void RenderSkybox() const;
	};
}
