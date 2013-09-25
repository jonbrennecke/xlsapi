#ifndef XLROW_H
#define XLROW_H

class XlsTable;

#include "xlscell.h"
#include <string>
#include <vector>

class XlsRow
{
public:
	// vars
	std::vector<XlsCell*> cells;

	// methods
	XlsRow(XlsTable*);
	XlsRow(const XlsRow&);
	XlsRow(XlsTable*, std::vector<std::string>);
	~XlsRow();
	XlsCell* addCell();
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
