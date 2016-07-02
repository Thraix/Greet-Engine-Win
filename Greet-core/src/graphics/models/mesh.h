#pragma once

#include <internal/greetgl.h>
#include <math/maths.h>
#include <logging\logger.h>
#include <vector>

namespace greet { namespace model {
	class Mesh
	{
	private:
		std::vector<uint> m_vbos;
		uint m_vaoId;
		uint m_iboId;
		uint m_vertexCount;
		uint m_indexCount;
		uint m_attributesCount;
		bool m_clockwise = false;

	public:
		Mesh(const float* vertices, const float* normals, const uint* colors, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(const float* vertices, const float* normals, const float* texCoords, const uint* colors, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(const float* vertices, const float* normals, uint color, uint vertexCount, const uint* indices, uint indexCount);
		Mesh(const float* vertices, const float* normals, const float* texCoords, uint color, uint vertexCount, const uint* indices, uint indexCount);
		virtual ~Mesh();
		inline uint getVAO()  const { return m_vaoId; };

		void render() const;

		void bind() const;
		void unbind() const;

		inline void setClockwiseRender(bool clockwise) { m_clockwise = clockwise; }
		inline bool isClockwiseRender() const { return m_clockwise; }
	private:
		void init(const float* vertices, const float* normals, const float* texCoords, const uint* colors, uint vertexCount, const uint* indices, uint indexCount);
		void addAttribute(uint attributeSize, const float* data);
		void addAttribute(uint attributeSize, const uint* data);
		void enableAttributes() const;
		void disableAttributes() const;
	};
}}