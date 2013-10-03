#include "sharedstrings.h"
#include "../sys/sys.hpp"
#include "xlsapi.h"
#include "xlsworksheet.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

/* Constructor */
XlsStream::XlsStream(const char* p)
{
    this->path = p;
    this->header = "<?xml version=\"1.0\"?>\n<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" "
        "xmlns:o=\"urn:schemas-microsoft-com:office:office\" "
        "xmlns:x=\"urn:schemas-microsoft-com:office:excel\" "
        "xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" "
        "xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n"
        "<Styles><Style ss:ID=\"yellow\"><Interior ss:Color=\"#ffff00\" ss:Pattern=\"Solid\"/></Style></Styles>";

    this->footer = "</Workbook>";
}

/* Alternate Constructor */
XlsStream::XlsStream()
{
    this->header = "<?xml version=\"1.0\"?>\n<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" "
        "xmlns:o=\"urn:schemas-microsoft-com:office:office\" "
        "xmlns:x=\"urn:schemas-microsoft-com:office:excel\" "
        "xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" "
        "xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n"
        "<Styles><Style ss:ID=\"yellow\"><Interior ss:Color=\"#ffff00\" ss:Pattern=\"Solid\"/></Style></Styles>";


    this->footer = "</Workbook>";
}

/* Destructor */
XlsStream::~XlsStream(){}

/* save the data stream as a *.xls file */
void XlsStream::saveXls(const char* path)
{
    // open & print header
    std::ofstream file;
    file.open(path);
    file << this->header;

    // print contents of worksheets
    for(int i=0;(unsigned int)i<this->worksheets.size();i++)
    {
        file << this->worksheets[i]->str();
    }

    // print footer & close
    file << this->footer;
    file.close();
}

/* save the data stream as a *.xlsx file */
void XlsStream::saveXlsx()
{

}

/* add a new *.xls format worksheet */
XlsWorksheet* XlsStream::addXlsWorksheet(std::string name)
{
    XlsWorksheet* sheet = new XlsWorksheet(name);
    this->worksheets.push_back(sheet);
    return sheet;
}

/* add the given worksheet */
XlsWorksheet* XlsStream::addXlsWorksheet(XlsWorksheet* sheet)
{
    this->worksheets.push_back(sheet);
    return sheet;
}

/* add a new *.xlsx format worksheet */
XlsWorksheet* XlsStream::addXlsxSheet(std::string path, std::string sheetname)
{
    XlsWorksheet* sheet = new XlsWorksheet(sheetname);
    this->worksheets.push_back(sheet);

    // unzip the file 'xl/worksheets/sheetX.xml' from the xlsx zip archive at 'path' 
    // note that '-p' returns the contents of the file to stdin
    std::string result = sys::terminal("unzip -p " + path + " xl/worksheets/" + sheetname + ".xml");
    std::vector<char> sheet_xml(result.begin(), result.end());
    sheet_xml.push_back('\0');

    // we use the rapidxml library to construct a DOM from the xml file
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&sheet_xml[0]);

    // navigate the XML DOM and look for any rows for the given sheet
    rapidxml::xml_node<>* wsheet = doc.first_node("worksheet");
    rapidxml::xml_node<>* sheetData = wsheet->first_node("sheetData");
    rapidxml::xml_node<>* row = sheetData->first_node("row");
    std::vector<int> indices;
    while (row != NULL)
    {
        indices.push_back(atoi(row->first_attribute("r")->value()));
        int diff = indices.back() - indices[indices.size()-2] -1;
        if(diff) { // handle any empty rows
            for(unsigned int i=0; i<diff;i++) sheet->addEmptyRow();
        }
        sheet->addXlsxRow(row,this->sharedstr);
        row = row->next_sibling("row");
    }
    return sheet;
}

/* get the worksheet at index */
XlsWorksheet* XlsStream::getSheet(int index)
{
    return this->worksheets[index];
}

/* Merge two XlsStream objects */
void XlsStream::merge(XlsStream* xls2, int worksheetIndex, int tableIndex)
{
    for(unsigned int i=0;i<xls2->worksheets.size();i++)
    {
        for(unsigned int j=0;j<xls2->worksheets[i]->tables.size();j++)
        {
            XlsTable* table = xls2->worksheets[i]->tables[j];
            XlsTable* table2 = this->worksheets.back()->tables.back();

            /*
            * The second file may begin at a different timestamp than when the first ends.
            * Thus, we need to correct for that by interpollating by generating artificial rows.
            */

            std::vector<std::string> tstamp1 = this->getTstamp(table2->rows.back());
            std::vector<std::string> tstamp2 = this->getTstamp(table->rows[2]);
            int diff = this->tstampCmp(tstamp1,tstamp2);

            // TODO clean this part up
            std::string full = table2->rows.back()->cells[0]->getValue();
            std::vector<std::string> matches = sys::split(full,',');
            std::vector<std::string> t = sys::split(matches[1],' ');
            std::string date = matches[0];
            std::string meridian = t[1];

            for(int k=1;k<diff/10;k++)
            {
                int sec = (atoi(tstamp1[2].c_str()) + k*10)%60;
                int min = atoi(tstamp1[1].c_str()) % 60 + (int)(atoi(tstamp1[2].c_str())+k*10)/60;

                std::stringstream ss;
                ss << date + " " << atoi(tstamp1[0].c_str()) << ":" << min << ":" << sec << " " + meridian;

                XlsRow *clone = this->worksheets[worksheetIndex-1]->tables.back()->rows.back()->copy();
                clone->cells[0]->setValue(ss.str());
                clone->cells[0]->setColor("yellow");
                this->worksheets[worksheetIndex-1]->tables[tableIndex-1]->addRow(clone);
            }

            /*
            *	add the rows from xls2
            *	start at k=2 because we don't need the first two rows
            */
            for(unsigned int k=2;k<table->rows.size();k++)
            {
                this->worksheets[worksheetIndex-1]->tables[tableIndex-1]->addRow(table->rows[k]);
            }
        }
    }
}

/*
* Generate tables from a *.txt file
*
* This method assumes the rows of the text file are delimitted by '\n'
* and that the columns are delimitted by '\t'
*/
void XlsStream::fromTxt(std::string s)
{
    XlsWorksheet *worksheet = this->addXlsWorksheet("Sheet1");
    XlsTable *table = worksheet->addXlsTable();

    std::ifstream ifs(s.c_str());
    std::string line;
    while(std::getline(ifs,line))
    {
        XlsRow *row = table->addRow();
        std::vector<std::string> matches = sys::split(line,'\t');
        for(unsigned int i=0;i<matches.size();i++)
        {
            XlsCell *cell = row->addXlsCell();
            cell->setValue(matches[i]);
        }
    }
}

/*
* Generate data structures from a *.xls file
*/
void XlsStream::fromXls(std::string path)
{
    // TODO
}

/*
*   Generate data structures from a *.xlsx file
*
*   An *.xlsx file is actually a zip archive of several files and folders
*   We retrieve the data to fill the XlsStream by selectively navigating the archive
*
*/
void XlsStream::fromXlsx(std::string path)
{
    this->sharedstr = new SharedStrings(path);
    std::vector<std::string> sheets = this->getXlsxSheetNames(path);
    for(unsigned int i=0;i<sheets.size();i++)
    {
        // add XlsWorksheet
        std::transform(sheets[i].begin(), sheets[i].end(), sheets[i].begin(), ::tolower);
        this->addXlsxSheet(path,sheets[i]);
    }
}

/*
*   return the names of any sheets from the *.xlsx file at 'path'
*/
std::vector<std::string> XlsStream::getXlsxSheetNames(std::string path)
{
    // unzip the file 'xl/workbook.xml' from the xlsx zip archive at 'path' 
    // note that '-p' returns the contents of the file to stdin
    std::string result = sys::terminal("unzip -p " + path + " xl/workbook.xml");
    std::vector<char> wbook_xml(result.begin(), result.end());
    wbook_xml.push_back('\0');

    // we use the rapidxml library to construct a DOM from the xml file
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&wbook_xml[0]);

    // navigate the XML DOM and look for any sheets
    rapidxml::xml_node<>* wbook = doc.first_node("workbook");
    rapidxml::xml_node<>* allsheets = wbook->first_node("sheets");
    rapidxml::xml_node<>* sheet = allsheets->first_node("sheet");

    std::vector<std::string> sheetnames;
    while (sheet != NULL)
    {
        std::string name = sheet->first_attribute("sheetId")->value(); 
        sheetnames.push_back("sheet" + name);
        sheet = sheet->next_sibling("sheet");
    }
    return sheetnames;
}

/*
* given a row, return the timestamp as an std::vector<std::string> of hour, minute, second
*/
std::vector<std::string> XlsStream::getTstamp(XlsRow* row)
{
    std::string tstamp = row->cells[0]->getValue();
    std::vector<std::string> matches = sys::split(tstamp,',');
    std::vector<std::string> t = sys::split(matches[1],' ');
    std::vector<std::string> ts = sys::split(t[0],':');
    return ts;
}

/*
*	Compare two timestamps, return the difference as (int) number of seconds between timestamps
*/
int XlsStream::tstampCmp(std::vector<std::string> tstamp1, std::vector<std::string> tstamp2)
{
    int s1 = atoi(tstamp1[2].c_str());
    int s2 = atoi(tstamp2[2].c_str());
    int m1 = atoi(tstamp1[1].c_str()) * 60;
    int m2 = atoi(tstamp2[1].c_str()) * 60;
    int h1 = atoi(tstamp1[0].c_str()) * 60;
    int h2 = atoi(tstamp2[0].c_str()) * 60;
    int t1 = h1  + m1 + s1;
    int t2 = h2  + m2 + s2;
    return t2 - t1;
}

/* set the path */
void XlsStream::setPath(const char* path)
{
    this->path = path;
}