#ifndef XLSSTREAM_H
#define XLSSTREAM_H

#include "xlsworksheet.h"
#include "sharedstrings.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

class XlsStream
{
public:
    
    // vars
    std::vector<XlsWorksheet*> worksheets;

    // methods
    XlsStream(const char*);
    XlsStream();
    ~XlsStream();
    XlsWorksheet* addXlsWorksheet(std::string);
    XlsWorksheet* addXlsWorksheet(XlsWorksheet*);
    XlsWorksheet* addXlsxSheet(std::string, std::string);
    XlsWorksheet* getSheet(int);
    void saveXls(const char*);
    void saveXlsx(); // TODO
    void merge(XlsStream*, int, int);
    void fromTxt(std::string);
    void fromXls(std::string); // TODO
    void fromXlsx(std::string);
    void setPath(const char*);

private:
    
    // vars
    const char* path;
    std::string header;
    std::string footer;
    SharedStrings *sharedstr;

    // methods
    std::vector<std::string> getXlsxSheetNames(std::string);


    // TODO: these methods are very user specific and 
    // should probably be added to a class that inherits from XlsStream
    // in order to keep XlsStream pure as a general purpose xls/xlsx input and output library
    std::vector<std::string> getTstamp(XlsRow*);
    int tstampCmp(std::vector<std::string>, std::vector<std::string>);

};

#endif
