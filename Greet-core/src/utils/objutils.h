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

	inline model::Mesh* convertToGobj(const std::string& filename)
	{
		std::vector<std::string> dataLine;

		std::vector<math::vec3> vertices;
		std::vector<math::vec2> texCoords;
		std::vector<math::vec3> normals;
		std::vector<uint> indices;
		std::vector<uint> indicesArray2;
		bool atIndex = false;

		float* texCoordsArray = NULL;
		float* normalsArray = NULL;

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
			else if (dataLine[0].compare("f") == 0)
			{
				if (!atIndex)
				{
					texCoordsArray = new float[vertices.size() * 2];
					normalsArray = new float[vertices.size() * 3];
					atIndex = true;
				}
				std::vector<std::string> vertex1 = split_string(dataLine[1], "/");
				std::vector<std::string> vertex2 = split_string(dataLine[2], "/");
				std::vector<std::string> vertex3 = split_string(dataLine[3], "/");

				processVertex(vertex1, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
				processVertex(vertex2, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
				processVertex(vertex3, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
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
		uint in = indices.size();
		fwrite(&v, sizeof(uint), 1, file);
		fwrite(&t, sizeof(uint), 1, file);
		fwrite(&n, sizeof(uint), 1, file);
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
		for (uint j : indicesArray2)
		{
			fwrite(&j, 1, sizeof(uint), file);
		}
		fwrite("GOBJ", 1, 4, file);
		fclose(file);
		return new model::Mesh(verticesArray, normalsArray, texCoordsArray, 0xffffffff, vertices.size(), indicesArray, indices.size());
	}

	inline void readFloats(FILE* file, uint& filePointer, float* floats, uint amount)
	{
		float* data = new float[amount+1];
		memset(data, 0, (amount + 1) * sizeof(float));
;		fread(data, sizeof(float), amount, file);
		for (uint i = 0;i < amount;i++)
		{
			floats[i] = data[i];
		}
		delete[] data;
	}

	inline void readUints(FILE* file, uint& filePointer, uint* uints, uint count, float* normalsArray, float* texCoordsArray, float* normals, float* texCoords)
	{
		uint* data = new uint[count+1];
		memset(data, 0, (count + 1)*sizeof(uint));
		fread(data, sizeof(uint), count, file);
		uint i = 0;
		for (uint j = 0;j < count;j += 3,i++)
		{
			uint vertex = data[j];
			uint texCoord = data[j + 1];
			uint normal = data[j + 2];
			uints[i] = vertex;
			texCoordsArray[vertex * 2] = texCoords[texCoord * 2];
			texCoordsArray[vertex * 2 + 1] = texCoords[texCoord * 2 + 1];
			normalsArray[vertex * 3] = normals[normal * 3];
			normalsArray[vertex * 3 + 1] = normals[normal * 3 + 1];
			normalsArray[vertex * 3 + 2] = normals[normal * 3 + 2];
		}
		memset(data, 0xffffffff, count*sizeof(uint));
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
		if (length < sizeof(char) * 4 + sizeof(uint) * 4)
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
			LOG_ERROR("OBJUTILS", "File format not supported, if you are using obj you need to compile it to gobj:",filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_FORMAT);
			return errorModel();
		}
		delete[] data;

		uint* uintData = new uint[4 + 1];
		memset(uintData, 0, (4 + 1)*sizeof(uint));
		fread(uintData, sizeof(uint), 4, file);
		uint vertexCount = uintData[0];
		uint texCoordCount = uintData[1];
		uint normalCount = uintData[2];
		uint indexCount = uintData[3];
		delete[] uintData;
		if (length < (vertexCount * 3 + texCoordCount * 2 + normalCount * 3) * sizeof(float) + indexCount * sizeof(uint))
		{
			fclose(file);
			LOG_ERROR("OBJUTILS","GOBJ file could not be read:",filename);
			ErrorHandle::setErrorCode(GREET_ERROR_GOBJ_READ);
			return errorModel();
		}
		float* vertices = new float[vertexCount * 3];
		float* texCoords = new float[texCoordCount * 2];
		float* normals = new float[normalCount * 3];
		uint* indices = new uint[indexCount];

		float* texCoordsArray = new float[vertexCount * 2];
		float* normalsArray = new float[vertexCount * 3];

		readFloats(file, pointer, vertices, vertexCount * 3);
		readFloats(file, pointer, texCoords, texCoordCount * 2);
		readFloats(file, pointer, normals, normalCount * 3);
		readUints(file, pointer, indices, indexCount * 3, normalsArray, texCoordsArray, normals, texCoords);
		fclose(file);
		return new model::Mesh(vertices,normalsArray,texCoordsArray, 0xffffffff,vertexCount,indices,indexCount);
	}

}}