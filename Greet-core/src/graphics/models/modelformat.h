#pragma once

#include <internal/greet_types.h>

namespace greet { namespace model {



	class ModelFormat
	{
	private:
		float* vertices;
		float* normals;
		uint* colors;
		float* texCoords;
		uint* indices;

		uint vertexCount;
		uint indexCount;

	public:
		ModelFormat(float* vertices, float* normals, float* texCoords, uint* colors, uint* indices, uint vertexCount, uint indexCount);
		ModelFormat(const std::string& filepath);
	};
}}