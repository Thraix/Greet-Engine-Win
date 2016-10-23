#include "MeshData.h"
#include <logging/logger.h>
namespace greet { namespace model {

	MeshData::MeshData(float* vertices, uint vertexCount, uint* indices, uint indexCount)
		: m_vertices(vertices), m_indices(indices), m_vertexCount(vertexCount), m_indexCount(indexCount)
	{
		
	}

	MeshData::~MeshData()
	{
		for (uint i = 0;i < m_data.size();i++)
		{
			delete m_data[i];
		}
		delete m_vertices;
		delete m_indices;
	}

	void MeshData::addAttribute(AttributeData* data)
	{
		m_data.push_back(data);
	}
}}