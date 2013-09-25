#include "xlsapi.h"
#include "xlsworksheet.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

/* Constructor */
XlsStream::XlsStream(char* p) 
{
	this->path = p;
	this->header = "<?xml version=\"1.0\"?>\n<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" "
	"xmlns:o=\"urn:schemas-microsoft-com:office:office\" "
	"xmlns:x=\"urn:schemas-microsoft-com:office:excel\" "
	"xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" "
	"xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n";

	this->footer = "</Workbook>";
}

/* Destructor */
XlsStream::~XlsStream(){}
 
/* Update the saved *.xls file */
void XlsStream::update() 
{
	std::ofstream file;
	if(this->path) 
	{
		// open & print header
		file.open(this->path);
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
}

/* add a new worksheet */
XlsWorksheet* XlsStream::addWorksheet(std::string name)
{
	XlsWorksheet* sheet = new XlsWorksheet(name);
	this->worksheets.push_back(sheet);
	return sheet;
} 

/* Merge two XlsStream objects */
void XlsStream::merge(XlsStream* xls2, int worksheetIndex, int tableIndex)
{
	for(int i=0;i<xls2->worksheets.size();i++)
	{
		for(int j=0;j<xls2->worksheets[i]->tables.size();j++)
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
			std::vector<std::string> matches = this->split(full,',');
			std::vector<std::string> t = this->split(matches[1],' ');
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
				clone->cells[0]->setColor("#00ff00");
				this->worksheets[worksheetIndex-1]->tables[tableIndex-1]->addRow(clone);
			}

			/* 
			*	add the rows from xls2
			*	start at k=2 because we don't need the first two rows
			*/
			for(int k=2;k<table->rows.size();k++)
			{
				this->worksheets[worksheetIndex-1]->tables[tableIndex-1]->addRow(table->rows[k]);
			}
		}
	}
	this->update();
}

/* 
* Generate tables from a *.txt file
* This method assumes the rows of the text file are delimitted by '\n'
* and that the columns are delimitted by '\t' 
*/
void XlsStream::fromTxt(std::string s) 
{
	XlsWorksheet *worksheet = this->addWorksheet("Sheet1");
	XlsTable *table = worksheet->addTable();

	std::ifstream ifs(s.c_str());
	std::string line;
	while(std::getline(ifs,line))
	{
		XlsRow *row = table->addRow();
		std::vector<std::string> matches = this->split(line,'\t');
		for(int i=0;i<matches.size();i++)
		{
			XlsCell *cell = row->addCell();
			cell->setValue(matches[i]);
		}
	}
	this->update();
}

/* 
*  std::getline will usually split a string at '\n', however, we can choose a 
*  cusom string delimiter
*/
std::vector<std::string> XlsStream::split(std::string s,char delim)
{
	std::vector<std::string> matches;
	std::istringstream iss(s);
	std::string token;
	while(std::getline(iss, token, delim))
		matches.push_back(token);
	return matches;
}

/* 
* given a row, return the timestamp as an std::vector<std::string> of hour, minute, second 
*/
std::vector<std::string> XlsStream::getTstamp(XlsRow* row)
{
	std::string tstamp = row->cells[0]->getValue();
	std::vector<std::string> matches = this->split(tstamp,',');
	std::vector<std::string> t = this->split(matches[1],' ');
	std::vector<std::string> ts = this->split(t[0],':');
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
