#include "xlsrow.h"
#include "xlstable.h"
// #include "sharedstrings.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

/* Constructor */
XlsRow::XlsRow()
{
    this->header = "\t<Row>\n";
    this->footer = "\t</Row>\n";
}

/* Copy Constructor */
XlsRow::XlsRow(const XlsRow& other)
{
    this->parent = other.parent;
    this->header = "\t<Row>\n";
    this->footer = "\t</Row>\n";
}

/* Alternate Constructor */
XlsRow::XlsRow(XlsTable* parent)
{
    this->parent = parent;
    this->header = "\t<Row>\n";
    this->footer = "\t</Row>\n";
}

/*
*	Alternate constructor
*	TODO
*/
XlsRow::XlsRow(XlsTable* parent, std::vector<std::string>)
{
    this->parent = parent;
    this->header = "\t<Row>\n";
    this->footer = "\t</Row>\n";
}

/* Destructor */
XlsRow::~XlsRow(){}

/* Append an empty cell to the row vector, return a pointer to it */
XlsCell* XlsRow::addXlsCell()
{
    this->parent->expColCount += 1;
    this->parent->updateHeader();
    XlsCell* cell = new XlsCell();
    this->cells.push_back(cell);
    return cell;
}

/* Append an empty cell to the row vector, return a pointer to it */
XlsCell* XlsRow::addXlsxCell(rapidxml::xml_node<>* cell, SharedStrings *sharedstr)
{
    XlsCell* xcell = new XlsCell();
    this->cells.push_back(xcell);
    rapidxml::xml_node<>* v = cell->first_node("v");
    int value = atoi(v->value());
    xcell->setValue(sharedstr->index(value));
    return xcell;
}

/* set the cell at i to value */
void XlsRow::setCell(int i, std::string value)
{

}

/* retrieve the cells contents as a formatted string */
std::string XlsRow::str()
{
    std::string s;
    for(unsigned int i=0;i<this->cells.size();i++)
    {
        s += this->cells[i]->str();
    }
    return this->header + s + this->footer;
}

/* return a duplicate XlsRow */
XlsRow* XlsRow::copy()
{
    XlsRow* clone = new XlsRow(this->parent);
    for(unsigned int i=0;i<this->cells.size();i++)
    {
        XlsCell* cell = clone->addXlsCell();
        cell->setValue(this->cells[i]->getValue());
    }
    return clone;
}