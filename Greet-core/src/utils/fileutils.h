#pragma once

#include <string>
#include <utils/log.h>
namespace greet { namespace utils{
	inline std::string read_file(const char* filepath)
	{
		FILE *file = fopen(filepath, "rt");
		if (!file)
		{
			GREET_ERROR("FILEUTILS","File could not be read: ", filepath);
			return "";
		}
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);
		std::string result(data);
		delete[] data;
		return result;
	}
	inline void write_file(const char* filepath, std::string write)
	{
		FILE *file = fopen(filepath,"wt");
		fseek(file, 0, SEEK_END);
		fputs(write.c_str(),file);
		fclose(file);
	}

	inline bool file_exists(const char* filepath)
	{
		if (FILE *file = fopen(filepath, "r"))
		{
			fclose(file);
			return true;
		}
		else
		{
			return false;
		}
	}
}}