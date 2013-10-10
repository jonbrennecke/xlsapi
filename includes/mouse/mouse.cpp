#include "../mex/mex.h"
#include "../sys/sys.hpp"
#include "mouse.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
// #include <stdio.h>

/* Constructor */
Mouse::Mouse()
{

}

/* Constructor */
Mouse::Mouse(XlsRow* row)
{
	// initialize member vars
	this->gender = row->cells[0]->getValue()[0];
	// mexPrintf(this->gender);
	this->filename = row->cells[1]->getValue();
	this->strain = row->cells[2]->getValue();
	this->id = atoi(row->cells[3]->getValue().c_str());
	this->group = row->cells[4]->getValue();
	this->transgender = (row->cells[5]->getValue()[0] == 'Y') ? true : false;
	this->intensity = atoi(std::vector<std::string>(sys::split(row->cells[6]->getValue(),' '))[0].c_str());

	// loop through trigger and random values and push_back their respective vectors
	int i = 8;
	std::string value = row->cells[7]->getValue();
	while(i<408) {
		this->trig.push_back(atof(value.c_str()));
		value = row->cells[i]->getValue();
		i++;
	}
	while(i<row->cells.size())
	{
		value = row->cells[i]->getValue();
		this->rand.push_back(atof(value.c_str()));
		i++;
	}
}

/* Destructor */
Mouse::~Mouse(){}

/* returns the mouse's private data as a vector */
std::vector<char*> Mouse::getData()
{
	std::stringstream ss;
	std::vector<char*> v;

	ss << this->gender;
	v.push_back((char*)ss.str().c_str());

	v.push_back((char*)this->filename.c_str());

	v.push_back((char*)this->strain.c_str());

	ss.str(std::string());
	ss << this->id;
	v.push_back((char*)ss.str().c_str());

	v.push_back((char*)this->group.c_str());
	v.push_back((this->transgender)?(char*)"Yes":(char*)"No");

	ss.str(std::string());
	ss << this->intensity;
	v.push_back((char*)ss.str().c_str());

	// for(int i=0;i<v.size();i++)
	// {
	// 	mexPrintf(v[i]);
	// }
	// mexPrintf((const char*)"\n");	
	return v;
}
