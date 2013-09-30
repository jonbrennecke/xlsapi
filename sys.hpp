#ifndef SYS_H
#define SYS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

namespace sys {

	/*
	*	getline implementation for grabbing stdin
	*/
	bool getl(FILE *f,std::string &line)
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
	std::string terminal(std::string command)
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

#endif
