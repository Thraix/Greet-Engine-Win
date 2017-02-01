#pragma once

#include <utils/json/JSONObject.h>
#include <utils/json/JSONArray.h>
#include <utils/fileutils.h>
#include <utils/stringutils.h>

namespace greet { namespace utils{
	
	class JSONLoader
	{
	public:
		static JSONObject loadJSON(const std::string& filename);
	private:

		static bool isKeyValue(const std::string& file, uint& currentPos, std::string* key, std::string* value, JSONObject* object, JSONArray* jsonArray, uint* type);
		static bool isValue(const std::string& file, uint& currentPos, std::string* value, JSONObject* object, JSONArray* jsonArray, uint* type);
		static bool isString(const std::string& file, uint& currentPos, std::string* value);
		static bool isNumber(const std::string& file, uint& currentPos, std::string* value);
		static bool isObject(const std::string& file, uint& currentPos, JSONObject* object);
		static bool isArray(const std::string& file, uint& currentPos, JSONArray* jsonArray);
		static void setString(const std::string& file, uint start, uint end, std::string* set);
		static bool isIndent(const std::string& file, uint& currentPos);

	};

}}