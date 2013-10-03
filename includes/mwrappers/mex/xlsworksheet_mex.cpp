#include "../../mex/mex.h"
#include "../../xlsapi/xlsapi.h"
#include "mexutils.hpp"
#include <string>
#include <stdio.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	char* cmd = cstrFromMx(prhs[0]);

    /* Constructor */
    if(!strcmp("new", cmd))
    {
        if (nlhs != 1)
            mexErrMsgTxt("Constructor: One output expected.");

        // Return a handle to a new C++ instance
        XlsWorksheet *xls = new XlsWorksheet();
        plhs[0] = convertPtr2Mat<XlsWorksheet>(xls);
        return;
    }

    /* Destructor */
    if(!strcmp("delete", cmd)) 
    {
        destroyObject<XlsWorksheet>(prhs[1]);
        return;
    }

    // Get instance pointer from the second input
    XlsWorksheet *xls = convertMat2Ptr<XlsWorksheet>(prhs[1]);

    /* getRow(int) */
    if(!strcmp("getRow", cmd)) 
    {
        char* index = cstrFromMx(prhs[2]);
        XlsRow* row = xls->getRow(atoi(index));
        plhs[0] = convertPtr2Mat(row);
        return;
    }

    /* return the number of rows */
    if(!strcmp("numel", cmd)) 
    {
        plhs[0] = mxCreateNumericMatrix(1, 1, mxINT16_CLASS, mxREAL);
        int * data = (int *) mxGetData(plhs[0]);
        data[0] = xls->rows.size();
        return;
    }

    /* add row */
    if(!strcmp("addRow", cmd))
    {
        XlsRow* row = convertMat2Ptr<XlsRow>(prhs[2]);
        xls->addRow(row);
        // plhs[0] = convertPtr2Mat<XlsRow>(row);
        return;
    }

    mxFree(cmd);

}