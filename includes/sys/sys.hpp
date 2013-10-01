// #ifndef SYS_H
// #define SYS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sys {

	/*
	*  std::getline will usually split a string at '\n', however, we can choose a
	*  cusom string delimiter
	*/
	static std::vector<std::string> split(std::string s,char delim)
	{
	    std::vector<std::string> matches;
	    std::istringstream iss(s);
	    std::string token;
	    while(std::getline(iss, token, delim))
	        matches.push_back(token);
	    return matches;
	}

	/*
	*	getline implementation for grabbing stdin
	*/
	static bool getl(FILE *f,std::string &line)
	{
		if (f == NULL) return false;
		else {
			char buffer[100];
			if(fgets(buffer, sizeof(buffer), f) != NULL)
			{
				line = buffer;
				return true;
			}
		}
	}
	
	/*
	*	send's "command" to terminal/cmd.exe and returns the result as a string
	*/
	static std::string terminal(std::string command)
	{
		FILE *file = popen(command.c_str(), "r");
		std::stringstream ss;
		std::string line;
		while(sys::getl(file,line))
		{
			ss << line;
		}
		pclose(file);
		return ss.str();
	}

}

// #endif