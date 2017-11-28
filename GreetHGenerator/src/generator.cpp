#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>
#include <algorithm>

std::string location = "../Greet-core/src/";
std::string include = "#include";
std::ofstream stream;

std::set<std::string> files;
std::set<std::string> filesLowercase;
std::set<std::string> filesChecked;

void addFile(const std::string& filename, std::set<std::string>::iterator& it)
{

	std::ifstream file(location + filename);
	std::string s;
	int line = 0;
	while (std::getline(file, s))
	{
		line++;
		if (s.length() <= include.length())
			continue;
		if (s.substr(0, include.length()) == include)
		{
			// String inside of <> or ""
			std::string inc = s.substr(include.length()+2, s.length() - 1 - (include.length() + 2));
			std::replace(inc.begin(), inc.end(), '\\', '/');
			if (files.count(inc) > 0)
			{
				auto found = files.find(inc);
				filesChecked.insert(inc);
				files.erase(found);
				if (found == it)
					it++;
				addFile(inc, it);
			}
			else if(filesChecked.count(inc) == 0)
			{
				std::string incCpy = inc;
				std::transform(incCpy.begin(), incCpy.end(), incCpy.begin(), ::tolower);
				if (filesLowercase.count(incCpy) > 0)
				{
					std::cout << "Wrong case in project(" << filename << ":" << line << "): " << inc << std::endl;
				}
			}
		}
	}
	file.close();

	stream << "#include <" << filename << ">\n";
}

void main()
{
	stream.open(location+"Greet.h");
	stream << "#pragma once\n\n";
	for (std::tr2::sys::recursive_directory_iterator i(location), end; i != end; ++i)
	{
		std::string str = i->path().generic_string();
		if (!is_directory(i->path()) && str[str.length() - 1] == 'h')
		{
			std::string s = std::string(str.c_str() + location.length());
			if (s == "Greet.h")
			{
				continue;
			}
			files.insert(s);
			std::string sCpy = s;
			std::transform(sCpy.begin(), sCpy.end(), sCpy.begin(), ::tolower);
			filesLowercase.insert(sCpy);
		}
	}

	for (auto it = files.begin();it != files.end();)
	{
		std::string filename = *it;
		filesChecked.insert(*it);
		files.erase(it++);
		addFile(filename, it);
	}
	stream.close();

	std::cout << "Generator Completed!" << std::endl;
	system("pause");
}