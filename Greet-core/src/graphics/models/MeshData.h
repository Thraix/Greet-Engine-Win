#pragma once

#include <logging\logger.h>
#include <internal/greetgl.h>
#include <internal/greet_types.h>
#include <vector>
namespace greet { namespace model { 

	struct AttributeDefaults
	{
		const uint location;
		const uint vertexValueSize;
		const uint memoryValueSize;
		const uint glType;
		const bool normalized;
		AttributeDefaults(uint location, uint vertexValueSize, uint memoryValueSize, uint glType, bool normalized)
			: location(location), vertexValueSize(vertexValueSize), memoryValueSize(memoryValueSize), glType(glType), normalized(normalized)
		{
		}

	};
	struct AttributeData
	{
	public:
		const uint location;
		const uint vertexValueSize;
		const uint memoryValueSize;
		const uint glType;
		const bool normalized;
		void* data;
		uint* uints = NULL;
		float* floats = NULL;
		byte* bytes = NULL;
	public:
		AttributeData(AttributeDefaults defaults, float* data) : location(defaults.location),vertexValueSize(defaults.vertexValueSize), memoryValueSize(defaults.memoryValueSize), glType(defaults.glType), normalized(defaults.normalized), data(data), floats(data) {}
		AttributeData(AttributeDefaults defaults, uint* data) : location(defaults.location),vertexValueSize(defaults.vertexValueSize), memoryValueSize(defaults.memoryValueSize), glType(defaults.glType), normalized(defaults.normalized), data(data), uints(data){}
		AttributeData(AttributeDefaults defaults, byte* data) : location(defaults.location),vertexValueSize(defaults.vertexValueSize), memoryValueSize(defaults.memoryValueSize), glType(defaults.glType), normalized(defaults.normalized), data(data), bytes(data){}

		virtual ~AttributeData() {
			if (uints != NULL)
				delete[] uints;
			else if (floats != NULL)
				delete[] floats;
			else if (bytes != NULL)
				delete[] bytes;
			else
				LOG_ERROR("ATTRIBUTEDATA", "Could not delete data, unknown type.");
		}
	};

	class MeshData
	{
	public:
		std::vector<AttributeData*> m_data;
		const float* m_vertices;
		const uint* m_indices;
		const uint m_vertexCount;
		const uint m_indexCount;
	public:
		MeshData(float* vertices, uint vertexCount, uint* indices, uint indexCount);
		virtual ~MeshData();
		void addAttribute(AttributeData* data);
	};
}}

#define ATTRIBUTE_COLOR		AttributeDefaults(MESH_COLORS_LOCATION, 4, sizeof(uint), GL_UNSIGNED_BYTE,GL_TRUE)
#define ATTRIBUTE_NORMAL	AttributeDefaults(MESH_NORMALS_LOCATION,3, sizeof(float) * 3,GL_FLOAT,GL_FALSE)
#define ATTRIBUTE_TEXCOORD	AttributeDefaults(MESH_TEXCOORDS_LOCATION,2, sizeof(float) * 2,GL_FLOAT,GL_FALSE)
