#include "xlsworksheet.h"
#include <string>
#include <sstream>

/* Constructor */
XlsWorksheet::XlsWorksheet(std::string name) 
{
	this->name = name;
	this->header = "<Worksheet ss:Name=\"" + name + "\">\n";
	this->footer = "</Worksheet>\n";
}

/* Destructor */
XlsWorksheet::~XlsWorksheet() {}

/* retrieve the worksheets contents as a formatted string */
std::string XlsWorksheet::str() 
{
	std::string s;
	for(int i=0;i<this->tables.size();i++)
	{
		s += this->tables[i]->str();
	}
	return this->header + s + this->footer;
}

/* add a table to the worksheet */
XlsTable* XlsWorksheet::addTable()
{
	XlsTable* table = new XlsTable();
	this->tables.push_back(table);
	return table;
}
