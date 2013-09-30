#include "../rapidxml-1.13/rapidxml.hpp"
#include "xlsworksheet.h"
#include "sharedstrings.h"
#include <string>
#include <sstream>
#include <iostream>

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
    std::stringstream ss;
    if(this->tables.size())
    {
        for(unsigned int i=0;i<this->tables.size();i++)
        {
            ss << this->tables[i]->str();
        }
    }
    else if(this->rows.size()) 
    {
        ss << "<Table ss:ExpandedColumnCount=\""<<this->rows.size()<<"\" ss:ExpandedRowCount=\""<<1<<"\" x:FullColumns=\"1\" x:FullRows=\"1\">\n";
        for(unsigned int i=0;i<this->rows.size();i++)
        {
            ss << this->rows[i]->str();
        }
        ss << "</Table>\n";
    }
    return this->header + ss.str() + this->footer;
}

/* add a table to the worksheet in *.xls format */
XlsTable* XlsWorksheet::addXlsTable()
{
    XlsTable* table = new XlsTable();
    this->tables.push_back(table);
    return table;
}

/* 
*   add a row to the worksheet in *.xlsx format 
*   XLSX format doesn't use tables, so we bypass the tables vector
*/
XlsRow* XlsWorksheet::addXlsxRow(rapidxml::xml_node<>* row, SharedStrings* sharedstr)
{
    XlsRow* xrow = new XlsRow();
    this->rows.push_back(xrow);

    rapidxml::xml_node<>* cell = row->first_node("c");
    while (cell != NULL)
    {
        XlsCell* xcell = xrow->addXlsxCell(cell, sharedstr);
        cell = cell->next_sibling("c");
    }
    return xrow;
}