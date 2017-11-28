#pragma once

#include <internal/GreetGL.h>
#include <math/Maths.h>
#include <logging\Logger.h>
#include <map>
#include <vector>
#include <graphics/textures/Texture.h>
#include <graphics/models/MeshData.h>
#include <utils/ErrorHandler.h>

namespace Greet {
	class Mesh
	{
	private:
		// Location, vbo
		std::map<uint,uint> m_vbos;
		uint m_vaoId;
		uint m_iboId;
		uint m_vertexCount;
		uint m_indexCount;
		bool m_culling = true;
		bool m_clockwise = false;

	public:
		Mesh(const vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(MeshData* data);
		void init(const vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		virtual ~Mesh();
		inline uint getVAO()  const { return m_vaoId; };

		void render() const;

		void bind() const;
		void unbind() const;

		inline void setClockwiseRender(bool clockwise) { m_clockwise = clockwise; }
		inline bool isClockwiseRender() const { return m_clockwise; }

		inline void setEnableCulling(bool culling) { m_culling = culling; }
		inline bool isEnableCulling() const { return m_culling; }
		void addAttribute(uint location, const vec3* data);
		void addAttribute(uint location, const vec2* data);
		//void addAttribute(uint location, uint attributeSize, const float* data);
		void addAttribute(uint location, uint attributeSize, const uint* data);
		void addAttribute(AttributeData* data);
		void setDefaultAttribute4f(uint location, const vec4& data);
		void setDefaultAttribute3f(uint location, const vec3& data);
	private:
		void enableAttributes() const;
		void disableAttributes() const;
	};
}