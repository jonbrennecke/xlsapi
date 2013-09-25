#include "xlstable.h"
#include <string>
#include <sstream>
#include <iostream>

/* Constructor */
XlsTable::XlsTable() 
{
	this->expColCount = 0;
	this->expRowCount = 0;
	this->fullColCount = 1;
	this->fullRowCount = 1;
	this->updateHeader();
	this->footer = "</Table>\n";
}

/* Destructor */
XlsTable::~XlsTable(){}

/* Add a row at index, push back everything else */
XlsRow* XlsTable::addRow(int index) 
{

}

/* 
*  Overload XlsTable::addRow() with a function that accepts no arguments. 
*  This method appends an empty XlsRow to the end of XlsTable->rows.
*/
XlsRow* XlsTable::addRow() 
{
	this->expRowCount += 1;
	this->updateHeader();
	XlsRow* row = new XlsRow(this);
	this->rows.push_back(row);
	return row;
}

/* 
*  Overload XlsTable::addRow() with a function that accepts an XlsRow* as an argument. 
*  This method appends the given XlsRow to the end of XlsTable->rows.
*/
XlsRow* XlsTable::addRow(XlsRow* row) 
{
	this->expRowCount += 1;
	this->updateHeader();
	this->rows.push_back(row);
	return row;
}

/* Add a column at index, push back everything else */
void XlsTable::addColumn(int index) 
{

}

/* set the cell at i,j to value */
void XlsTable::setCell(int i, int j, std::string value)
{

}

/* retrieve the worksheets contents as a formatted string */
std::string XlsTable::str() 
{
	std::string s;
	for(int i=0;i<this->rows.size();i++)
	{
		s += this->rows[i]->str();
	}
	return this->header + s + this->footer;
}

/* update the header with new row and column counts */
void XlsTable::updateHeader()
{
	std::stringstream s;
	s << "<Table ss:ExpandedColumnCount=\"" << this->expColCount << "\" ss:ExpandedRowCount=\"" << this->expRowCount; 
	s << "\" x:FullColumns=\"" << this->fullColCount << "\" x:FullRows=\"" << this->fullRowCount << "\">\n";
	this->header = s.str();
}
