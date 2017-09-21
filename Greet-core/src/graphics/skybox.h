#pragma once

#include <graphics/textures/cubemap.h>
#include <graphics/models/camera.h>
#include <graphics/shaders/shader.h>
#include <graphics\models\mesh.h>
#include <graphics/models/meshfactory.h>
#include <graphics\shaders\shaderfactory.h>

namespace Greet {
	
	class Skybox
	{
	private:
		CubeMap* m_map;
		Shader* m_shader;
		Mesh* m_mesh;
	public:
		Skybox(CubeMap* map);
		const CubeMap* getCubeMap() const { return m_map; };
		virtual ~Skybox();
		void render(const mat4& projectionMatrix, const Camera& camera) const;
	};
}