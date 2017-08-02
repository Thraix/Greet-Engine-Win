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

	std::ostream& operator<<(std::ostream& os, const JSONArray& arr)
	{
		os << JSON::get_indent() << "[\n";
		JSON::push_indent();
		uint size = arr.m_objects.size();
		for (uint i = 0;i<size;++i)
		{
			os << arr.getObject(i);
			if(i != size - 1)
			{ 
				os << ",\n" << JSON::get_indent();
			}
		}
		JSON::pop_indent();
		os << "\n" << JSON::get_indent() << "]";
		return os;
	}
}}