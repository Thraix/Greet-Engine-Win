#include "JSONArray.h"

#include "JSONObject.h"

namespace greet { namespace utils {
	
	JSONArray::JSONArray()
	{
	
	}

	JSONArray::JSONArray(const JSONArray& jsonArray)
		: m_objects(jsonArray.m_objects)
	{
	
	}

	JSONArray::JSONArray(std::vector<JSONObject> objects)
		: m_objects(objects)
	{
	
	}

	void JSONArray::addObject(JSONObject object)
	{
		m_objects.push_back(object);
	}

	JSONObject JSONArray::getObject(size_t i) const
	{
		size_t size = m_objects.size();
		if (i >= size)
		{
			LOG_ERROR("JSONARRAY","Index is out of bounds:",i,">=",size);
			if (size != 0)
			{
				return getObject(0);
			}
			return JSONObject();
		}
		return m_objects[i];
	}

	JSONObject JSONArray::operator[](size_t i) const
	{
		return getObject(i);
	}
}}