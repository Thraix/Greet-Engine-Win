#pragma once

#include <utils/json/JSON.h>
#include <utils/json/JSONArray.h>
#include <internal/GreetTypes.h>
#include <logging/Log.h>
#include <map>
#include <vector>
#include <utils/StringUtils.h>

namespace Greet {

	class JSONObject
	{
		friend JSONArray;

	private:
		// Static Null values
		static std::string valueNull;
		static JSONObject objectNull;
		static JSONArray arrayNull;

		std::map<std::string, std::string> m_values;
		std::map<std::string, JSONArray> m_arrays;
		std::map<std::string, JSONObject> m_objects;

	public:
		JSONObject();
		JSONObject(const JSONObject& object);
		JSONObject(std::map<std::string,std::string> values,std::map<std::string,JSONObject> objects,std::map<std::string,JSONArray> arrays);

		bool hasKey(const std::string& key);

		void addValue(std::string key, std::string value);
		void addArray(std::string key, JSONArray value);
		void addObject(std::string key, JSONObject value);

		const std::string& getValue(const std::string& key) const;
		float getValueAsFloat(const std::string& key) const;
		bool getValueAsBool(const std::string& key) const;
		bool isNull(const std::string& key) const;

		const JSONArray& getArray(const std::string& key) const;
		const JSONObject& getObject(const std::string& key) const;

		friend std::ostream& operator<<(std::ostream& os, const JSONObject& obj);
	};

}