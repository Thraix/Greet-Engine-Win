#include "JSONLoader.h"

namespace Greet {

	JSONObject JSONLoader::loadJSON(const std::string& filename)
	{
		std::string file = FileUtils::read_file(filename.c_str());
		uint currentPos = file.find("{");
		while (isIndent(file, currentPos));
		JSONObject obj;
		if (!isObject(file, currentPos,&obj))
		{
			Log::error("Invalid format: ",currentPos,file[currentPos] == ' ');
			return JSONObject();
		}
		while (isIndent(file, currentPos));
		if (currentPos != file.size())
		{
			Log::info("JSONObject ended but there is more in the file.");
			return JSONObject();
		}
		return obj;
	}

	bool JSONLoader::isValue(const std::string& file, uint& currentPos, std::string* value, JSONObject* object, JSONArray* jsonArray, uint* type)
	{
		uint lastPos = currentPos;
		std::string s = file.substr(currentPos,4);
		currentPos += 4;
		if (s == "null")
		{
			*value = "null";
			*type = 0;
			return true;
		}
		if (s == "true")
		{
			*value = "true";
			*type = 0;
			return true;
		}
		currentPos = lastPos;
		s = file.substr(currentPos,5);
		currentPos += 5;
		if (s == "false")
		{
			*type = 0;
			*value = "false";
			return true;
		}
		currentPos = lastPos;
		if (isString(file, currentPos, value))
		{
			*type = 0;
			return true;
		}
		if (isNumber(file, currentPos, value))
		{
			*type = 0;
			return true;
		}
		if (isObject(file, currentPos, object))
		{
			*type = 1;
			return true;
		}
		if (isArray(file, currentPos, jsonArray))
		{
			*type = 2;
			return true;
		}
		return false;
	}

	bool JSONLoader::isObject(const std::string& file, uint& currentPos, JSONObject* object)
	{
		JSONObject retObject;
		std::string key;
		std::string value;
		JSONObject obj;
		JSONArray jsonArray;
		uint type;
		uint lastPos = currentPos;
		while (isIndent(file, currentPos));
		char c = file[currentPos++];
		if (c != '{')
		{
			currentPos = lastPos;
			return false;
		}
		do
		{
			while (isIndent(file, currentPos));
			if (!isKeyValue(file, currentPos, &key, &value, &obj, &jsonArray, &type))
			{
				currentPos = lastPos;
				Log::info("Argument in JSONObject doesn't have a key or value");
				return false;
			}
			if (type == 0)
			{
				retObject.addValue(key, value);
				value = "";
			}
			else if (type == 1)
			{
				retObject.addObject(key, obj);
				obj = JSONObject();
			}
			else if (type == 2)
			{
				retObject.addArray(key,jsonArray);
				jsonArray = JSONArray();
			} 
			while (isIndent(file, currentPos));
			c = file[currentPos++];
		} while (c == ',');

		currentPos--;
		while (isIndent(file, currentPos));
		c = file[currentPos++];
		if (c != '}')
		{
			currentPos = lastPos;
			return false;
		}
		*object = retObject;
		return true;
	}

	bool JSONLoader::isArray(const std::string& file, uint& currentPos, JSONArray* jsonArray)
	{
		JSONObject object;
		uint lastPos = currentPos;
		char c = file[currentPos++];
		if (c != '[')
		{
			currentPos = lastPos;
			return false;
		}
		do {
			while (isIndent(file, currentPos));
			if (!isObject(file, currentPos, &object))
			{
				currentPos = lastPos;
				return false;
			}
			jsonArray->addObject(object);
			object = JSONObject(); // Reset JSONObject

			while (isIndent(file, currentPos));
			c = file[currentPos++];
		} while (c == ',');
		currentPos--;
		while (isIndent(file, currentPos));
		c = file[currentPos++];
		if (c != ']')
		{
			currentPos = lastPos;
			return false;
		}
		return true;
	}

	bool JSONLoader::isKeyValue(const std::string& file, uint& currentPos, std::string* key, std::string* value, JSONObject* object, JSONArray* jsonArray, uint* type)
	{
		uint lastPos = currentPos;
		std::string keyValue;
		if (!isString(file, currentPos,&keyValue))
		{
			currentPos = lastPos;
			return false;
		}
		while (isIndent(file, currentPos));
		char c = file[currentPos++];
		if (c != ':')
		{
			currentPos = lastPos;
			return false;
		}
		while (isIndent(file, currentPos));
		if (!isValue(file,currentPos,value,object,jsonArray,type))
		{
			currentPos = lastPos;
			return false;
		}
		*key = keyValue;
		return true;
	}

	bool JSONLoader::isString(const std::string& file, uint& currentPos, std::string* value)
	{
		uint lastPos = currentPos;
		char c = file[currentPos++];
		if (c != '\"')
		{
			currentPos = lastPos;
			return false;
		}
		c = file[currentPos++];
		while (c != '\"' && c != std::string::npos)
		{
			if (c == '\\')
			{
				c = file[currentPos++];
				if (c != '\"' && c != '\\' && c != '/' && c != 'b' && c != 'f' && c != 'n' && c != 'r' && c != 't' && c != 'u') {
					currentPos = lastPos;
					return false;
				}
				if (c == 'u')
				{
					for (int i = 0;i < 4;i++)
					{
						c = file[currentPos++];
						if ((c < '0' || c > '9') && (c < 'a' || c > 'f'))
						{
							currentPos = lastPos;
							return false;
						}
					}
				}
			}
			c = file[currentPos++];
		}
		std::string retValue;
		setString(file,lastPos,currentPos,&retValue);
		retValue = retValue.substr(1,retValue.size()-2); // remove both " around string
		StringUtils::replace_all(retValue, "\\\"", "\"");
		StringUtils::replace_all(retValue, "\\\\", "\\");
		StringUtils::replace_all(retValue, "\\/", "\/");
		StringUtils::replace_all(retValue, "\\b", "\b");
		StringUtils::replace_all(retValue, "\\f", "\f");
		StringUtils::replace_all(retValue, "\\n", "\n");
		StringUtils::replace_all(retValue, "\\r", "\r");
		StringUtils::replace_all(retValue, "\\t", "\t");
		//replace_all(retValue, "\\u", "\u");
		*value = retValue;
		return true;
	}

	bool JSONLoader::isNumber(const std::string& file, uint& currentPos, std::string* value)
	{
		uint lastPos = currentPos;
		char c = file[currentPos++];
		if (c != '-' && (c < '0' || c > '9'))
		{
			currentPos = lastPos;
			return false;
		}
		if (c == '-')
		{
			c = file[currentPos++];
		}
		if (c >= '1' && c <= '9')
		{
			c = file[currentPos++];
			while (c >= '0' && c <= '9')
				c = file[currentPos++];
			uint pos = currentPos;
			if (c == '.')
			{
				c = file[currentPos++];
				if (c < '0' || c > '9')
				{
					currentPos = pos;
					setString(file,lastPos,currentPos,value);
					return true;
				}
				while (c >= '0' && c <= '9')
					c = file[currentPos++];
			}
			currentPos--;
			setString(file,lastPos,currentPos,value);
			return true;
		}
		else // if c == '0'
		{
			c = file[currentPos++];
			if (c != '.')
			{
				currentPos--;
				setString(file,lastPos,currentPos,value);
				return true;
			}
			c = file[currentPos++];
			if (c < '0' || c > '9')
			{
				currentPos = lastPos;
				return false;
			}
			c = file[currentPos++];
			while (c >= '0' && c <= '9')
				c = file[currentPos++];
			currentPos--;
			setString(file,lastPos,currentPos,value);
			return true;
		}
		setString(file,lastPos,currentPos,value);
		return true;
	}


	void JSONLoader::setString(const std::string& file, uint start, uint end, std::string* set)
	{
		*set = file.substr(start,end-start);
	}

	bool JSONLoader::isIndent(const std::string& file, uint& currentPos)
	{
		char c = file[currentPos++];
		if (c != '\t' && c != '\n' && c != ' ')
		{
			currentPos--;
			return false;
		}
		return true;
	}
}