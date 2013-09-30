#ifndef SHAREDSTR_H
#define SHAREDSTR_H

#include "../rapidxml-1.13/rapidxml.hpp"
#include <string>
#include <vector>

class SharedStrings
{
public:
	SharedStrings(std::string);
	~SharedStrings();
	std::string index(int);

private:
	std::vector<std::string> strings;
};

#endif