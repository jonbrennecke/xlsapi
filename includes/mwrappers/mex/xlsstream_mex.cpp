#include "../../mex/mex.h"
#include "../../xlsapi/xlsapi.h"
#include "mexutils.hpp"
#include <string>
#include <stdio.h>
#include <typeinfo>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	char* cmd = cstrFromMx(prhs[0]);

    /* Constructor */
    if(!strcmp("new", cmd))
    {
        if (nlhs != 1)
            mexErrMsgTxt("Constructor: One output expected.");
        
        // Return a handle to a new C++ instance
        XlsStream *xls = new XlsStream();
        plhs[0] = convertPtr2Mat<XlsStream>(xls);
        return;
    }

    /* Destructor */
    if(!strcmp("delete", cmd)) 
    {
        destroyObject<XlsStream>(prhs[1]);
        return;
    }

    // Get instance pointer from the second input
    XlsStream *xls = convertMat2Ptr<XlsStream>(prhs[1]);
  
  	/* saveXls() */
    if(!strcmp("saveXls", cmd)) 
    {
        char* path = cstrFromMx(prhs[2]);
        xls->saveXls(path);
        return;
    }

    /* fromXlsx(std::string) */
    if(!strcmp("fromXlsx", cmd))
    {
    	char* path = cstrFromMx(prhs[2]);
        xls->fromXlsx(path);
        return;
    }

    /* getSheet */
    if(!strcmp("getSheet", cmd))
    {
        char* index = cstrFromMx(prhs[2]);
        XlsWorksheet* wsheet = xls->getSheet(atoi(index));
        plhs[0] = convertPtr2Mat(wsheet);
        return;
    }

    /* addWorksheet */
    if(!strcmp("addWorksheet", cmd))
    {
        XlsWorksheet* sheet = convertMat2Ptr<XlsWorksheet>(prhs[2]);
        xls->addXlsWorksheet(sheet);
        // plhs[0] = convertPtr2Mat<XlsWorksheet>(sheet);
        return;
    }

    mxFree(cmd);

}