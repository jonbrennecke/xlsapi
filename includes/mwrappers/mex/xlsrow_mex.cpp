#include "../../mex/mex.h"
#include "../../xlsapi/xlsapi.h"
#include "mexutils.hpp"
#include <string>
#include <stdio.h>
#include <vector>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char* cmd = cstrFromMx(prhs[0]);

    /* Constructor */
    if(!strcmp("new", cmd))
    {
        if (nlhs != 1)
            mexErrMsgTxt("Constructor: One output expected.");
        // Return a handle to a new C++ instance
        XlsRow *row = new XlsRow();
        plhs[0] = convertPtr2Mat<XlsRow>(row);
        return;
    }

    /* Destructor */
    if(!strcmp("delete", cmd)) 
    {
        destroyObject<XlsRow>(prhs[1]);
        return;
    }

    // Get instance pointer from the second input
    XlsRow *row = convertMat2Ptr<XlsRow>(prhs[1]);

    if(!strcmp("numel", cmd)) 
    {
        plhs[0] = mxCreateNumericMatrix(1, 1, mxINT16_CLASS, mxREAL);
        int * data = (int *) mxGetData(plhs[0]);
        data[0] = row->cells.size();
        return;
    }

    /* get the cells as an array of chars */
    if(!strcmp("cells", cmd)) 
    {
        const char *str[row->cells.size()];
        for(int i=0;i<row->cells.size();i++)
        {
            str[i] = row->cells[i]->getValue().c_str();
        }
        plhs[0] = mxCreateCharMatrixFromStrings(row->cells.size(), (const char **)str);
        return;
    }

    /* build the row from an mxMatrix */
    if(!strcmp("addCellsFromStrings", cmd)) 
    {
        const mxArray *data = prhs[2];
        int n = mxGetM(data);
        for(int i=0;i<n;i++)
        {
            mxArray *mx = mxGetCell(data, i);
            char* cstr = cstrFromMx(mx);
            if(cstr!=NULL)
            {
                std::string str = std::string(cstr);
                XlsCell *cell = new XlsCell(str); 
                row->addXlsCell(cell);
            }          
        }
        return;
    }
    


    mxFree(cmd);

}