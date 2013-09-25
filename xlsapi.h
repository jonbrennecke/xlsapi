#ifndef XLSSTREAM_H
#define XLSSTREAM_H

#include "xlsworksheet.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

class XlsStream
{
public:
	// vars
	std::vector<XlsWorksheet*> worksheets;

	// methods
	XlsStream(char*);
	~XlsStream();
	void update();
	XlsWorksheet* addWorksheet(std::string); 
	void merge(XlsStream*, int, int);
	void fromTxt(std::string);

private:
	// vars
	char* path;
	std::string header;
	std::string footer;

	// methods
	std::vector<std::string> split(std::string,char);
	std::vector<std::string> getTstamp(XlsRow*);
	int tstampCmp(std::vector<std::string>, std::vector<std::string>);

};

#endif
