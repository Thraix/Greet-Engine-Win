#pragma once

#include <vector>
#include <internal/Greetgl.h>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <logging/log.h>
#include <graphics/renderers/renderer.h>
#include <graphics\models\entitymodel.h>
#include <graphics\models\camera.h>
#include <graphics/skybox.h>


namespace Greet{

	class Renderer3D : public Renderer
	{

	protected:
		mat4 m_projectionMatrix;
		Camera* m_camera;
		float m_renderDistance;
		float m_near;
		float m_far;
		Skybox* m_skybox;


	public:
		Renderer3D(float width, float height, Camera* camera, float fov, float near, float far, Skybox* skybox)
			: m_projectionMatrix(mat4::projectionMatrix(width/height, fov, near, far)), m_camera(camera), m_skybox(skybox), m_renderDistance(far), m_near(near), m_far(far)
		{
			
		}
		virtual ~Renderer3D() 
		{
			delete m_skybox;
		}

		virtual void render(const EntityModel& model) const;
		virtual void render(const Mesh& model) const;
		virtual void render(const MaterialModel& model) const;

		virtual void update(float timeElapsed);

		virtual void submit(const EntityModel* model) {};

		virtual void begin() {
			renderSkybox();
		};
		virtual void render() const {};
		virtual void end() {};
	private:
		void renderSkybox() const;
	};
}
