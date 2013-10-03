#ifndef MOUSE_H
#define MOUSE_H

#include "../xlsapi/xlsapi.h"
#include <string>
#include <vector>

class Mouse
{
public:
	//vars
	std::vector<float> trig;
	std::vector<float> rand;

	// methods
	Mouse();
	Mouse(XlsRow*);
	~Mouse();
	std::vector<char*> getData();


private:

	// vars
	char gender;
	std::string filename;
	std::string strain;
	std::string group;
	int id;
	int intensity;
	bool transgender;

};

#endif