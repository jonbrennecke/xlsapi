#include "xlscell.h"

#include <string>
#include <sstream>


/* Constructor */
XlsCell::XlsCell() 
{
	this->header = "\t\t<Cell><Data ss:Type=\"String\">";
	this->footer = "</Data></Cell>\n";
}

/* Destructor */
XlsCell::~XlsCell() {}

/* set the cell to value */
void XlsCell::setValue(std::string value)
{
	this->value = value;
}

/* set the cell to value */
void XlsCell::setColor(std::string color)
{
	this->header = "\t\t<Cell><Data ss:Color=\""+color+"\" ss:Type=\"String\">";
}

std::string XlsCell::getValue()
{
	return this->value;
}

/* retrieve the cells contents as a formatted string */
std::string XlsCell::str() 
{
	return this->header + this->value + this->footer;
}