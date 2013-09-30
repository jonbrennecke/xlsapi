#include "includes/xlsapi/xlsapi.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{

	// std::vector<std::string> args(argv + 1,argv + argc + !argc);

	XlsStream *xlsApp = new XlsStream();
	xlsApp->fromXlsx("test.xlsx");

	xlsApp->setPath("test.xls");
	xlsApp->saveXls();

	return 0;
}