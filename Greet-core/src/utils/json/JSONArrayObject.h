#pragma once

#include <internal/greet_types.h>
#include <vector>

/* *
	Not currently supported
*/
namespace greet { namespace utils {

	class JSONObject;
	class JSONArray;

	class JSONArrayObject
	{
		friend class JSONObject;
		friend class JSONArray;
	private:
		std::vector<std::string> m_values;
		std::vector<JSONObject> m_objects;
		std::vector<JSONArray> m_arrays;
	public:
		JSONArrayObject(std::vector<std::string> values,std::vector<JSONObject> objects, std::vector<JSONArray> arrays);
		JSONArrayObject(std::string* values, uint valueSize, JSONObject* objects, uint objectSize, JSONArray* arrays, uint arraySize);

	};
}}
