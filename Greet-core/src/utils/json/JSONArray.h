#pragma once

#include <utils/json/JSON.h>
#include <vector>
#include <set>

namespace Greet {

	class JSONObject;

	class JSONArray
	{
		friend class JSONObject;
	private:
		std::vector<JSONObject> m_objects;
	public:
		JSONArray();
		JSONArray(const JSONArray& jsonArray);
		JSONArray(std::vector<JSONObject> objects);
		void addObject(JSONObject object);
		inline JSONObject getObject(size_t i) const;
		JSONObject operator[](size_t i) const;

		friend std::ostream& operator<<(std::ostream& os, const JSONArray& dt);
	};

}