#pragma once

#include <vector>
#include <graphics/models/mesh.h>
#include <string>
#include <utils/fileutils.h>
#include <utils/stringutils.h>

#define GOBJ_VECTOR3_SIZE sizeof(float) * 3 // 13
#define GOBJ_VECTOR2_SIZE sizeof(float) * 2 // 9
#define GOBJ_UINT_SIZE sizeof(uint)			// 5
#define GOBJ_BUFFER_SIZE 1024

namespace greet { namespace utils {


	inline model::Mesh* errorModel()
	{
		return NULL;// TODO return cube
	}

	inline math::vec3 loadVector3(std::vector<std::string> dataLine)
	{
		return math::vec3(atof(dataLine[1].c_str()), atof(dataLine[2].c_str()), atof(dataLine[3].c_str()));
	}

	inline math::vec2 loadVector2(std::vector<std::string> dataLine)
	{
		return math::vec2(atof(dataLine[1].c_str()), atof(dataLine[2].c_str()));
	}

	inline void processVertex(const std::vector<std::string>& vertexData, std::vector<uint>& indices, std::vector<uint>& indicesArray, const std::vector<math::vec2>& texCoords, const std::vector<math::vec3>& normals, float* texCoordsArray, float* normalsArray)
	{
		uint currentVertex = atoi(vertexData[0].c_str()) - 1;

		indices.push_back(currentVertex);
		indicesArray.push_back(currentVertex);
		uint texPos = atoi(vertexData[1].c_str()) - 1;
		math::vec2 currentTex = texCoords[texPos];
		indicesArray.push_back(texPos);
		texCoordsArray[currentVertex * 2] = currentTex.x;
		texCoordsArray[currentVertex * 2 + 1] = currentTex.y;
		uint normalPos = atoi(vertexData[2].c_str()) - 1;
		math::vec3 currentNormal = normals[normalPos];
		indicesArray.push_back(normalPos);
		normalsArray[currentVertex * 3] = currentNormal.x;
		normalsArray[currentVertex * 3 + 1] = currentNormal.y;
		normalsArray[currentVertex * 3 + 2] = currentNormal.z;
	}

	inline void readFloats(FILE* file, uint& filePointer, float* floats, uint amount)
	{
		float* data = new float[amount + 1];
		memset(data, 0, (amount + 1) * sizeof(float));
		fread(data, sizeof(float), amount, file);
		for (uint i = 0;i < amount;i++)
		{
			floats[i] = data[i];
		}
		delete[] data;
	}

	inline void readFloatsAsUints(FILE* file, uint& filePointer, uint* uints, uint amount)
	{
		float* data = new float[amount * 3 + 1];
		memset(data, 0, (amount * 3 + 1) * sizeof(float));
		fread(data, sizeof(float), amount * 3, file);
		for (uint i = 0;i < amount;i++)
		{
			uints[i] = ((uint)(255 * data[i * 3]) << 16) | ((uint)(255 * data[i * 3]) << 8) | (uint)(255 * data[i * 3]);
		}
		delete[] data;
	}

	inline void readIndices(FILE* file, uint& filePointer, uint* uints, uint indices, uint indexSize, bool hasNormals, float* normalsArray, float* normals, bool hasTexCoords, float* texCoordsArray, float* texCoords, bool hasColors, uint* colorsArray, uint* colors)
	{
		uint* data = new uint[indices * indexSize + 1];
		memset(data, 0, (indices * indexSize + 1)*sizeof(uint));
		fread(data, sizeof(uint), indices * indexSize, file);
		for (uint i = 0;i < indices;i++)
		{
			uint j = 0;
			uint vertex = data[j];
			j++;
			if (hasNormals)
			{
				uint normal = data[j];
				normalsArray[vertex * 3] = normals[normal * 3];
				normalsArray[vertex * 3 + 1] = normals[normal * 3 + 1];
				normalsArray[vertex * 3 + 2] = normals[normal * 3 + 2];
				j++;
			}
			if (hasTexCoords)
			{
				uint texCoord = data[j];
				normalsArray[vertex * 2] = normals[texCoord * 2];
				normalsArray[vertex * 2 + 1] = normals[texCoord * 2 + 1];
				j++;
			}
			if (hasColors)
			{
				uint color = data[j];
				colorsArray[vertex] = normals[color];
				j++;
			}
		}
		memset(data, 0xffffffff, indices*indexSize*sizeof(uint));
		delete[] data;
	}

	inline model::Mesh* loadObj(const std::string& filename)
	{

		FILE *file = fopen(filename.c_str(), "rb");
		if (!file)
		{
			LOG_ERROR("OBJUTILS", "Obj could not be read:", filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_READ);
			return errorModel();
		}
		uint pointer = 0;

		char* data = new char[5];
		fseek(file, 0, SEEK_END);
		ulong length = ftell(file);
		fseek(file, 0, SEEK_SET);
		if (length < sizeof(char) * 8 + sizeof(uint) * 5)
		{
			fclose(file);
			LOG_ERROR("OBJUTILS", "File format not supported, if you are using obj you need to compile it to gobj:", filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_FORMAT);
			return errorModel();
		}
		memset(data, 0, 5);
		fread(data, sizeof(char), 4, file);
		if (std::string(data).compare("GOBJ") != 0)
		{
			fclose(file);
			LOG_ERROR("OBJUTILS", "File format not supported, if you are using obj you need to compile it to gobj:", filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_FORMAT);
			return errorModel();
		}
		delete[] data;

		uint* uintData = new uint[6 + 1];
		memset(uintData, 0, (6 + 1)*sizeof(uint));
		fread(uintData, sizeof(uint), 6, file);
		uint version = uintData[0];
		if (version != 2)
		{
			LOG_ERROR("OBJUTILS", "GOBJ has wrong version:",version, filename);
			return errorModel();
		}
		uint vertexCount = uintData[1];
		uint normalCount = uintData[2];
		uint texCoordCount = uintData[3];
		uint colorCount = uintData[4];
		uint indexCount = uintData[5];
		delete[] uintData;
		if (length < (vertexCount * 3 + texCoordCount * 2 + normalCount * 3) * sizeof(float) + indexCount * sizeof(uint))
		{
			fclose(file);
			LOG_ERROR("OBJUTILS", "GOBJ file could not be read:", filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_READ);
			return errorModel();
		}
		float* vertices = new float[vertexCount * 3];
		float* normals = new float[normalCount * 3];
		float* texCoords = new float[texCoordCount * 2];
		uint* colors = new uint[colorCount];
		uint* indices = new uint[indexCount];

		float* normalsArray = new float[vertexCount * 3];
		float* texCoordsArray = new float[vertexCount * 2];
		uint* colorsArray = new uint[vertexCount];
		if (vertexCount > 0)
			readFloats(file, pointer, vertices, vertexCount * 3);
		if (normalCount > 0)
			readFloats(file, pointer, normals, normalCount * 3);
		if (texCoordCount > 0)
			readFloats(file, pointer, texCoords, texCoordCount * 2);
		if (colorCount > 0)
			readFloatsAsUints(file, pointer, colors, colorCount);

		uint indexSize = vertexCount == 0 ? 1 : 0
			+ texCoordCount == 0 ? 1 : 0
			+ normalCount == 0 ? 1 : 0
			+ colorCount == 0 ? 1 : 0;

		readIndices(file, pointer, indices, indexCount, indexSize, normalCount == 0, normalsArray, normals, texCoordCount == 0, texCoordsArray, texCoords, colorCount == 0, colorsArray, colors);
		fclose(file);

		// Process data to format
		return new model::Mesh(vertices, normalsArray, texCoordsArray, 0xffffffff, vertexCount, indices, indexCount);
	}


	inline model::Mesh* convertToGobj(const std::string& filename)
	{
		std::vector<std::string> dataLine;

		std::vector<math::vec3> vertices;
		std::vector<math::vec2> texCoords;
		std::vector<math::vec3> normals;
		std::vector<math::vec3> colors;
		std::vector<uint> indices;
		bool atIndex = false;

		std::ifstream input(filename);
		for (std::string line; getline(input, line); )
		{
			dataLine = split_string(line, " ");
			if (dataLine[0].compare("v") == 0)
			{
				math::vec3 vector = loadVector3(dataLine);
				vertices.push_back(vector);
			}
			else if (dataLine[0].compare("vt") == 0)
			{
				math::vec2 texCoord = loadVector2(dataLine);
				texCoords.push_back(texCoord);
			}
			else if (dataLine[0].compare("vn") == 0)
			{
				math::vec3 normal = loadVector3(dataLine);
				normals.push_back(normal);
			}
			else if (dataLine[0].compare("c") == 0)
			{
				math::vec3 color = loadVector3(dataLine);
				colors.push_back(color);
			}
			else if (dataLine[0].compare("f") == 0)
			{
				std::vector<std::string> vertex1 = split_string(dataLine[1], "/");
				std::vector<std::string> vertex2 = split_string(dataLine[2], "/");
				std::vector<std::string> vertex3 = split_string(dataLine[3], "/");
				for (int i = 0;i < vertex1.size();i++)
				{
					indices.push_back(atoi(vertex1[i].c_str()));
				}
				for (int i = 0;i < vertex2.size();i++)
				{
					indices.push_back(atoi(vertex2[i].c_str()));
				}
				for (int i = 0;i < vertex3.size();i++)
				{
					indices.push_back(atoi(vertex3[i].c_str()));
				}
			}
		}

		input.close();
		float* verticesArray = new float[vertices.size() * 3];
		uint* indicesArray = new uint[indices.size()];
		int i = 0;
		for (math::vec3 vertex : vertices)
		{
			verticesArray[i++] = vertex.x;
			verticesArray[i++] = vertex.y;
			verticesArray[i++] = vertex.z;
		}
		for (uint i = 0;i < indices.size();i++)
		{
			indicesArray[i] = indices[i];
		}

		FILE *file = fopen((filename + ".gobj").c_str(), "wb+");
		if (!file)
		{
			LOG_ERROR("OBJUTILS", "Obj could not be read:", filename);
			return errorModel(); // TODO return cube model
		}

		fwrite("GOBJ",4,1,file);
		uint v = vertices.size();
		uint t = texCoords.size();
		uint n = normals.size();
		uint c = colors.size();
		uint indexSize = v==0 ? 1 : 0 
			+ t == 0 ? 1 : 0
			+ n == 0 ? 1 : 0
			+ c == 0 ? 1 : 0;
		uint in = indices.size()/indexSize;
		uint version = 2;
		fwrite(&version,sizeof(uint),1,file);
		fwrite(&v, sizeof(uint), 1, file);
		fwrite(&n, sizeof(uint), 1, file);
		fwrite(&t, sizeof(uint), 1, file);
		fwrite(&c, sizeof(uint), 1, file);
		fwrite(&in, sizeof(uint), 1, file);
		uint j = 0;
		for (math::vec3 vertex : vertices)
		{
			uint f = ftell(file);
			fwrite(&vertex.x, sizeof(float), 1, file);
			fwrite(&vertex.y, sizeof(float), 1, file);
			fwrite(&vertex.z, sizeof(float), 1, file);
			j++;
		}

		for (math::vec2 texCoord : texCoords)
		{
			fwrite(&texCoord.x, sizeof(float), 1, file);
			fwrite(&texCoord.y, sizeof(float), 1, file);
		}

		for (math::vec3 normal : normals)
		{
			fwrite(&normal.x, sizeof(float), 1, file);
			fwrite(&normal.y, sizeof(float), 1, file);
			fwrite(&normal.z, sizeof(float), 1, file);
		}
		for (uint i : indices)
		{
			fwrite(&i, 1, sizeof(uint), file);
		}
		fwrite("GOBJ", 1, 4, file);
		fclose(file);
		return loadObj(filename+".gobj");
	}
}}