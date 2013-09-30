#ifndef XLCELL_H
#define XLCELL_H

#include <string>

class XlsCell
{
public:
    XlsCell();
    ~XlsCell();
    void setValue(std::string);
    void setColor(std::string);
    std::string getValue();
    std::string str();

private:
    std::string header;
    std::string footer;
    std::string value;
};

#endif
