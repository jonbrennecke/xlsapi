#ifndef XLSWORKSHEET_H
#define XLSWORKSHEET_H

#include "xlstable.h"
#include <string>
#include <vector>

class XlsWorksheet
{
public:
	// vars
	std::vector<XlsTable*> tables;

	// methods
	XlsWorksheet(std::string);
	~XlsWorksheet();
	std::string str();
	XlsTable* addTable();

private:
	// vars
	std::string name;
	std::string header;
	std::string footer;
};

#endif
