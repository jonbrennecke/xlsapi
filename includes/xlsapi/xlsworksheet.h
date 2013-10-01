#ifndef XLSWORKSHEET_H
#define XLSWORKSHEET_H

#include "xlstable.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "sharedstrings.h"
#include <string>
#include <vector>

class XlsWorksheet
{
public:

    // vars
    std::vector<XlsTable*> tables; // used for *.xls format
    std::vector<XlsRow*> rows; // used for *.xlsx format


    // methods
    XlsWorksheet(std::string);
    ~XlsWorksheet();
    std::string str();
    XlsTable* addXlsTable();
    XlsRow* addXlsxRow(rapidxml::xml_node<>*,SharedStrings*);
    XlsRow* addEmptyRow();
    std::string getName();

private:

    // vars
    std::string name;
    std::string header;
    std::string footer;
};

#endif
