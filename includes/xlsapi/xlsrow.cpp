#include "xlsrow.h"
#include "xlstable.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

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

    rapidxml::xml_node<>* prev = cell->previous_sibling("c");
    if(prev!=NULL)
    {
        int before = (int)prev->first_attribute("r")->value()[0];
        int after = (int)cell->first_attribute("r")->value()[0]; 
        int diff = after - before;
        if(strlen(prev->first_attribute("r")->value())==3)
        {
            int before2 = (int)prev->first_attribute("r")->value()[1];
            int after2 = (int)cell->first_attribute("r")->value()[1];
            int diff2 = after2 - before2;
            diff = diff + diff2;
        }
        if(diff)
        {
            for(int i=0;i<diff-1;i++)
            {
                this->cells.push_back(new XlsCell());
            }
        }
    }
    rapidxml::xml_node<>* v = cell->first_node("v"); 
    rapidxml::xml_attribute<>* t = cell->first_attribute("t");
    if(v!=NULL)
    {
        int value = atoi(v->value());
        if(t==NULL)
        {
            xcell->setValue(v->value());
        }
        else {
            // if(t->value()=="s") TODO implement this; right now we're only considering one case
            sharedstr->index(value);
            xcell->setValue(sharedstr->index(value));
        }
    }
    this->cells.push_back(xcell);
    return xcell;
}

/* get the cell at index */
XlsCell* XlsRow::getCell(int index)
{
    return this->cells[index];
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