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

namespace Greet { namespace ObjUtils {


	inline Mesh* errorModel()
	{
		return NULL;// TODO return cube
	}

	inline vec3 loadVector3(std::vector<std::string> dataLine)
	{
		return vec3(atof(dataLine[1].c_str()), atof(dataLine[2].c_str()), atof(dataLine[3].c_str()));
	}

	inline vec2 loadVector2(std::vector<std::string> dataLine)
	{
		return vec2(atof(dataLine[1].c_str()), atof(dataLine[2].c_str()));
	}

	inline void processVertex(const std::vector<std::string>& vertexData, std::vector<uint>& indices, std::vector<uint>& indicesArray, const std::vector<vec2>& texCoords, const std::vector<vec3>& normals, vec2* texCoordsArray, vec3* normalsArray)
	{
		uint currentVertex = atoi(vertexData[0].c_str()) - 1;

		indices.push_back(currentVertex);
		indicesArray.push_back(currentVertex);
		uint texPos = atoi(vertexData[1].c_str()) - 1;
		vec2 currentTex = texCoords[texPos];
		indicesArray.push_back(texPos);
		texCoordsArray[currentVertex] = currentTex;
		uint normalPos = atoi(vertexData[2].c_str()) - 1;
		vec3 currentNormal = normals[normalPos];
		indicesArray.push_back(normalPos);
		normalsArray[currentVertex] = currentNormal;
	}

	inline Mesh* convertToGobj(const std::string& filename)
	{
		std::vector<std::string> dataLine;

		std::vector<vec3> vertices;
		std::vector<vec2> texCoords;
		std::vector<vec3> normals;
		std::vector<uint> indices;
		std::vector<uint> indicesArray2;
		bool atIndex = false;

		vec2* texCoordsArray = NULL;
		vec3* normalsArray = NULL;

		std::ifstream input(filename);
		for (std::string line; getline(input, line); )
		{
			dataLine = StringUtils::split_string(line, " ");
			if (dataLine[0].compare("v") == 0)
			{
				vec3 vector = loadVector3(dataLine);
				vertices.push_back(vector);
			}
			else if (dataLine[0].compare("vt") == 0)
			{
				vec2 texCoord = loadVector2(dataLine);
				texCoords.push_back(texCoord);
			}
			else if (dataLine[0].compare("vn") == 0)
			{
				vec3 normal = loadVector3(dataLine);
				normals.push_back(normal);
			}
			else if (dataLine[0].compare("f") == 0)
			{
				if (!atIndex)
				{
					texCoordsArray = new vec2[vertices.size()];
					normalsArray = new vec3[vertices.size()];
					atIndex = true;
				}
				std::vector<std::string> vertex1 = StringUtils::split_string(dataLine[1], "/");
				std::vector<std::string> vertex2 = StringUtils::split_string(dataLine[2], "/");
				std::vector<std::string> vertex3 = StringUtils::split_string(dataLine[3], "/");

				processVertex(vertex1, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
				processVertex(vertex2, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
				processVertex(vertex3, indices, indicesArray2, texCoords, normals, texCoordsArray, normalsArray);
			}
		}

		input.close();
		vec3* verticesArray = new vec3[vertices.size()];
		uint* indicesArray = new uint[indices.size()];
		int i = 0;
		for (vec3 vertex : vertices)
		{
			verticesArray[i++] = vertex;

		}
		for (uint i = 0;i < indices.size();i++)
		{
			indicesArray[i] = indices[i];
		}

		FILE *file = fopen((filename + ".gobj").c_str(), "wb+");
		if (!file)
		{
			Log::error("Obj could not be read: ", filename);
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
		for (vec3 vertex : vertices)
		{
			uint f = ftell(file);
			fwrite(&vertex.x, sizeof(float), 1, file);
			fwrite(&vertex.y, sizeof(float), 1, file);
			fwrite(&vertex.z, sizeof(float), 1, file);
			j++;
		}

		for (vec2 texCoord : texCoords)
		{
			fwrite(&texCoord.x, sizeof(float), 1, file);
			fwrite(&texCoord.y, sizeof(float), 1, file);
		}

		for (vec3 normal : normals)
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
		Mesh* mesh = new Mesh(verticesArray, vertices.size(), indicesArray, indices.size());
		mesh->addAttribute(MESH_NORMALS_LOCATION, normalsArray);
		mesh->addAttribute(MESH_TEXCOORDS_LOCATION, texCoordsArray);
		return mesh;
	}

	inline void readVec2s(FILE* file, uint& filePointer, vec2* vec2s, uint amount)
	{
		vec2* data = new vec2[amount + 1];
		fread((float*)data, sizeof(float), amount * 2, file);
		for (uint i = 0;i < amount;i++)
		{
			vec2s[i] = data[i];
		}
		delete[] data;
	}

	inline void readVec3s(FILE* file, uint& filePointer, vec3* vec3s, uint amount)
	{
		vec3* data = new vec3[amount + 1];
		fread((float*)data, sizeof(float), amount * 3, file);
		for (uint i = 0;i < amount;i++)
		{
			vec3s[i] = data[i];
		}
		delete[] data;
	}

	inline void readUints(FILE* file, uint& filePointer, uint* uints, uint count, vec3* normalsArray, vec2* texCoordsArray, vec3* normals, vec2* texCoords)
	{
		uint* data = new uint[count*3+1];
		fread(data, sizeof(uint), count * 3, file);
		uint i = 0;
		for (uint j = 0;j < count * 3;j += 3,i++)
		{
			uint vertex = data[j];
			uint texCoord = data[j + 1];
			uint normal = data[j + 2];
			uints[i] = vertex;
			texCoordsArray[vertex] = texCoords[texCoord];
			normalsArray[vertex] = normals[normal];
		}
		memset(data, 0xffffffff, count * 3 * sizeof(uint));
		delete[] data;
	}

	inline Mesh* loadObj(const std::string& filename)
	{

		FILE *file = fopen(filename.c_str(), "rb");
		if (!file)
		{
			Log::error("Obj could not be read: ", filename);
			ErrorHandle::setErrorCode(Greet_ERROR_GOBJ_READ);
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
			Log::error("File format not supported, if you are using obj you need to compile it to gobj: ", filename);
			ErrorHandle::setErrorCode(Greet_ERROR_GOBJ_FORMAT);
			return errorModel();
		}
		data[4] = '\0';
		fread(data, sizeof(char), 4, file);
		if (std::string(data).compare("GOBJ") != 0)
		{
			fclose(file);
			Log::error("File format not supported, if you are using obj you need to compile it to gobj: ",filename);
			ErrorHandle::setErrorCode(Greet_ERROR_GOBJ_FORMAT);
			return errorModel();
		}
		delete[] data;

		uint* uintData = new uint[4 + 1];
		fread(uintData, sizeof(uint), 4, file);
		uint vertexCount = uintData[0];
		uint texCoordCount = uintData[1];
		uint normalCount = uintData[2];
		uint indexCount = uintData[3];
		delete[] uintData;
		if (length < (vertexCount * 3 + texCoordCount * 2 + normalCount * 3) * sizeof(float) + indexCount * sizeof(uint))
		{
			fclose(file);
			Log::error("GOBJ file could not be read: ",filename);
			ErrorHandle::setErrorCode(Greet_ERROR_GOBJ_READ);
			return errorModel();
		}
		vec3* vertices = new vec3[vertexCount];
		vec2* texCoords = new vec2[texCoordCount];
		vec3* normals = new vec3[normalCount];
		uint* indices = new uint[indexCount];

		vec2* texCoordsArray = new vec2[vertexCount];
		vec3* normalsArray = new vec3[vertexCount];

		readVec3s(file, pointer, vertices, vertexCount);
		readVec2s(file, pointer, texCoords, texCoordCount);
		readVec3s(file, pointer, normals, normalCount);
		readUints(file, pointer, indices, indexCount, normalsArray, texCoordsArray, normals, texCoords);
		ulong pos = ftell(file);
		fclose(file);
		Mesh* mesh = new Mesh(vertices, vertexCount, indices, indexCount);
		mesh->addAttribute(MESH_NORMALS_LOCATION, normalsArray); 
		mesh->addAttribute(MESH_TEXCOORDS_LOCATION, texCoordsArray);
		return mesh;
	}

}}