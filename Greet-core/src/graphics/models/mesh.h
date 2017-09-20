#pragma once

#include <internal/greetgl.h>
#include <math/maths.h>
#include <logging\logger.h>
#include <map>
#include <vector>
#include <graphics/textures/texture.h>
#include <graphics/models/meshdata.h>
#include <utils/errorhandler.h>

namespace greet { namespace model {
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
		Mesh(const math::vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(MeshData* data);
		void init(const math::vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		virtual ~Mesh();
		inline uint getVAO()  const { return m_vaoId; };

		void render() const;

		void bind() const;
		void unbind() const;

		inline void setClockwiseRender(bool clockwise) { m_clockwise = clockwise; }
		inline bool isClockwiseRender() const { return m_clockwise; }

		inline void setEnableCulling(bool culling) { m_culling = culling; }
		inline bool isEnableCulling() const { return m_culling; }
		void addAttribute(uint location, const math::vec3* data);
		void addAttribute(uint location, const math::vec2* data);
		//void addAttribute(uint location, uint attributeSize, const float* data);
		void addAttribute(uint location, uint attributeSize, const uint* data);
		void addAttribute(AttributeData* data);
		void setDefaultAttribute4f(uint location, const math::vec4& data);
		void setDefaultAttribute3f(uint location, const math::vec3& data);
	private:
		void enableAttributes() const;
		void disableAttributes() const;
	};
}}