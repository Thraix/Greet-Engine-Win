#pragma once

#include <vector>
#include <internal/greetgl.h>
#include <math/maths.h>
#include <graphics/fonts/font.h>
#include <logging/logger.h>
#include <graphics/renderers/renderer.h>
#include <graphics\models\entitymodel.h>
#include <graphics\models\camera.h>


namespace greet{ namespace graphics{

	class Renderer3D : public Renderer
	{

	private:
		math::mat4 m_projectionMatrix;
		const model::Camera& m_camera;
		float m_renderDistance;


	public:
		Renderer3D(float width, float height, const model::Camera& camera, float fov, float near, float far)
			: m_renderDistance(far),m_projectionMatrix(math::mat4::projectionMatrix(width/height, fov, near, far)), m_camera(camera)
		{
			
		}
		virtual ~Renderer3D() {}

		void submit(const model::Mesh& mesh) const;
		void submit(const model::MaterialModel& model) const;
		void submitSkybox(const model::MaterialModel& model) const;
		void submit(const model::EntityModel& model) const;
	private:
		math::mat4 getTransformationMatrix(const model::EntityModel& model) const;
	};
}}
