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
    if(!strcmp("fromStr", cmd)) 
    {
        std::vector<char*> v;

        // const mxArray *data = prhs[3];

        int m = mxGetM(prhs[2]);
        int n = mxGetN(prhs[2]);
        char str[m];
        mxGetString(prhs[2], str, n);
        mexPrintf(str);
        // mxGetString(prhs[3],);
        // if(data==NULL)
        // {
        //     mexPrintf("here");
        // }
        // mwSize size = mxGetNumberOfElements(data);
        // char* str = cstrFromMx(prhs[3]);

        // mwSize size = mxGetNumberOfElements(data);
        // mwIndex index;
        // const mxArray *element;
        // mexPrintf("size: %s\n",str);
        // for(int i=0;i<size;i++)
        // {
        // //     // data[i];
        // //     // v.push_back(cstrFromMx(prhs[i]));
        // }

        // nfields = mxGetNumberOfFields(prhs[0]);
        // NStructElems = mxGetNumberOfElements(prhs[0]);
        return;
    }
    


    mxFree(cmd);

}