#pragma once

#include <vector>
#include <internal/greetgl.h>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <logging/logger.h>
#include <graphics/renderers/renderer.h>
#include <graphics\models\entitymodel.h>
#include <graphics\models\camera.h>
#include <graphics/skybox.h>


namespace greet{ namespace graphics{

	class Renderer3D : public Renderer
	{

	protected:
		math::mat4 m_projectionMatrix;
		model::Camera* m_camera;
		float m_renderDistance;
		float m_near;
		float m_far;
		Skybox* m_skybox;


	public:
		Renderer3D(float width, float height, model::Camera* camera, float fov, float near, float far, Skybox* skybox)
			: m_projectionMatrix(math::mat4::projectionMatrix(width/height, fov, near, far)), m_camera(camera), m_skybox(skybox), m_renderDistance(far), m_near(near), m_far(far)
		{
			
		}
		virtual ~Renderer3D() 
		{
			delete m_skybox;
		}

		virtual void render(const model::EntityModel& model) const;
		virtual void render(const model::Mesh& model) const;
		virtual void render(const model::MaterialModel& model) const;

		virtual void update(float timeElapsed);

		virtual void submit(const model::EntityModel* model) {};

		virtual void begin() {
			renderSkybox();
		};
		virtual void render() const {};
		virtual void end() {};
	private:
		void renderSkybox() const;
	};
}}
