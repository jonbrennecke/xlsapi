#ifndef XLROW_H
#define XLROW_H

class XlsTable;

#include "sharedstrings.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "xlscell.h"
#include <string>
#include <vector>

class XlsRow
{
public:
    // vars
    std::vector<XlsCell*> cells;

    // methods
    XlsRow();
    XlsRow(XlsTable*);
    XlsRow(const XlsRow&);
    XlsRow(XlsTable*, std::vector<std::string>);
    ~XlsRow();
    XlsCell* addXlsCell();
    XlsCell* addXlsxCell(rapidxml::xml_node<>*, SharedStrings *sharedstr);
    void setCell(int, std::string);
    std::string str();
    XlsRow* copy();

private:

    // vars
    XlsTable* parent;
    std::string header;
    std::string footer;
};

#endif
