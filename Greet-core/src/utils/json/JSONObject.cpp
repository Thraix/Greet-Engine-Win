#include "JSONObject.h"

namespace greet { namespace utils {

	std::string JSONObject::valueNull;
	JSONObject JSONObject::objectNull;
	JSONArray JSONObject::arrayNull;

	JSONObject::JSONObject()
	{
			
	}

	JSONObject::JSONObject(const JSONObject& object)
		:m_values(object.m_values), m_objects(object.m_objects), m_arrays(object.m_arrays)
	{
	
	}
	JSONObject::JSONObject(std::map<std::string,std::string> values, std::map<std::string,JSONObject> objects,std::map<std::string,JSONArray> arrays)
		: m_values(values), m_objects(objects), m_arrays(arrays)
	{

	}

	bool JSONObject::hasKey(const std::string& key)
	{
		if (m_values.find(key) != m_values.end())
			return true;
		if (m_objects.find(key) != m_objects.end())
			return true;
		if (m_arrays.find(key) != m_arrays.end())
			return true;
		return false;
	}

	void JSONObject::addValue(std::string key, std::string value)
	{
		if (hasKey(key))
		{
			LOG_ERROR("JSONOBJECT", "Key already defined in JSONObject:", key);
			return;
		}
		m_values[key] = value;
	}
	void JSONObject::addArray(std::string key, JSONArray value)
	{
		if (hasKey(key))
		{
			LOG_ERROR("JSONOBJECT", "Key already defined in JSONObject:", key);
			return;
		}
		m_arrays[key] = value;
	}
	void JSONObject::addObject(std::string key, JSONObject value)
	{
		if (hasKey(key))
		{
			LOG_ERROR("JSONOBJECT", "Key already defined in JSONObject:", key);
			return;
		}
		m_objects[key] = value;
	}

	const std::string& JSONObject::getValue(const std::string& key) const
	{
		auto it = m_values.find(key);
		if (it == m_values.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return valueNull;
		}
		return it->second;
	}

	float JSONObject::getValueAsFloat(const std::string& key) const
	{
		auto it = m_values.find(key);
		if (it == m_values.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return 0.0f;
		}
		return atof(it->second.c_str());
	}
	
	bool JSONObject::getValueAsBool(const std::string& key) const
	{
		auto it = m_values.find(key);
		if (it == m_values.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return 0.0f;
		}
		return it->second == "true";
	}

	bool JSONObject::isNull(const std::string& key) const
	{
		auto it = m_values.find(key);
		if (it == m_values.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return 0.0f;
		}
		return it->second == "null";
	}

	const JSONArray& JSONObject::getArray(const std::string& key) const
	{
		auto it = m_arrays.find(key);
		if (it == m_arrays.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return arrayNull;
		}
		return it->second;
		
	}

	const JSONObject& JSONObject::getObject(const std::string& key) const
	{
		auto it = m_objects.find(key);
		if (it == m_objects.end())
		{
			LOG_ERROR("JSONOBJECT", "Key does not exist in JSONObject:", key);
			return objectNull;
		}
		return it->second;
	
	}
}}