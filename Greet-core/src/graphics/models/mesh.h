#pragma once

#include <internal/GreetGL.h>
#include <math/Maths.h>
#include <logging/Logger.h>
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
		Mesh(const Vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(MeshData* data);
		void init(const Vec3* vertices, uint vertexCount, const uint* indices, uint indexCount);
		virtual ~Mesh();
		inline uint GetVAO()  const { return m_vaoId; };

		void Render() const;

		void Bind() const;
		void Unbind() const;

		inline void SetClockwiseRender(bool clockwise) { m_clockwise = clockwise; }
		inline bool IsClockwiseRender() const { return m_clockwise; }

		inline void SetEnableCulling(bool culling) { m_culling = culling; }
		inline bool IsEnableCulling() const { return m_culling; }
		void AddAttribute(uint location, const Vec3* data);
		void AddAttribute(uint location, const Vec2* data);
		//void addAttribute(uint location, uint attributeSize, const float* data);
		void AddAttribute(uint location, uint attributeSize, const uint* data);
		void AddAttribute(AttributeData* data);
		void SetDefaultAttribute4f(uint location, const Vec4& data);
		void SetDefaultAttribute3f(uint location, const Vec3& data);
	private:
		void EnableAttributes() const;
		void DisableAttributes() const;
	};
}