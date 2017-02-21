#pragma once

#include <graphics/textures/cubemap.h>
#include <graphics/models/camera.h>
#include <graphics/shaders/shader.h>
#include <graphics\models\mesh.h>
#include <graphics/models/meshfactory.h>
#include <graphics\shaders\shaderfactory.h>

namespace greet { namespace graphics {
	

	class Skybox
	{
	private:
		CubeMap* m_map;
		Shader* m_shader;
		model::Mesh* m_mesh;
	public:
		Skybox(CubeMap* map);
		const CubeMap* getCubeMap() const { return m_map; };
		virtual ~Skybox();
		void render(const math::mat4& projectionMatrix, const model::Camera& camera) const;
	};
}}