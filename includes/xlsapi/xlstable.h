#ifndef XLSTABLE_H
#define XLSTABLE_H

#include "xlsrow.h"
#include <string>
#include <vector>

class XlsTable
{
public:
    // vars
    int expColCount;
    int expRowCount;
    int fullColCount;
    int fullRowCount;
    std::vector<XlsRow*> rows;

    // methods
    XlsTable();
    ~XlsTable();
    std::string str();
    XlsRow* addRow(int);
    XlsRow* addRow();
    XlsRow* addRow(XlsRow*);
    void addColumn(int);
    void setCell(int, int, std::string);
    void updateHeader();

private:
    // vars
    std::string header;
    std::string footer;
};

#endif
