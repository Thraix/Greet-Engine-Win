#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>
#include <algorithm>

std::string location = "../Greet-core/src/";
std::string include = "#include";
std::ofstream stream;

void addFile(const std::string& filename, std::set<std::string>& files, std::set<std::string>::iterator& it)
{

	std::ifstream file(location + filename);
	std::string s;
	while (std::getline(file, s))
	{
		if (s.length() <= include.length())
			continue;
		if (s.substr(0, include.length()) == include)
		{
			std::string inc = s.substr(include.length()+2, s.length() - 1 - (include.length() + 2));
			std::replace(inc.begin(), inc.end(), '\\', '/');
			std::transform(inc.begin(), inc.end(), inc.begin(), ::tolower);
			if (files.count(inc) > 0)
			{
				auto found = files.find(inc);
				files.erase(found);
				if (found == it)
					it++;
				addFile(inc, files, it);
			}
		}
	}
	file.close();

	stream << "#include <" << filename << ">\n";
}

void main()
{
	stream.open(location+"greet.h");
	stream << "#pragma once\n";
	std::set<std::string> files;
	for (std::tr2::sys::recursive_directory_iterator i(location), end; i != end; ++i)
	{
		std::string str = i->path().generic_string();
		if (!is_directory(i->path()) && str[str.length() - 1] == 'h')
		{
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			std::string s = std::string(str.c_str() + location.length());
			if (s == "greet.h")
			{
				continue;
			}
			files.insert(s);
		}
	}

	for (auto it = files.begin();it != files.end();)
	{
		std::string filename = *it;
		files.erase(it++);
		addFile(filename, files,it);
	}
	stream.close();
}