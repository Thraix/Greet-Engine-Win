#pragma once

#include <graphics/textures/CubeMap.h>
#include <graphics/models/Camera.h>
#include <graphics/shaders/Shader.h>
#include <graphics/models/Mesh.h>
#include <graphics/models/MeshFactory.h>
#include <graphics/shaders/ShaderFactory.h>

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