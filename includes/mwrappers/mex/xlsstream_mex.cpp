#include "../../mex/mex.h"
#include "../../xlsapi/xlsapi.h"
#include "mexutils.hpp"
#include <string>
#include <stdio.h>

char* cstrFromMx(const mxArray* input)
{
	char* cstr;
    cstr = mxArrayToString(input);
    return cstr;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	// char *cmd;
 //    cmd = mxArrayToString(prhs[0]);
 //    mexPrintf("%s\n", cmd);

	char* cmd = cstrFromMx(prhs[0]);
	mexPrintf("%s\n", cmd);

    /* Constructor */
    if(!strcmp("new", cmd))
    {
        if (nlhs != 1)
            mexErrMsgTxt("Constructor: One output expected.");
        // Return a handle to a new C++ instance
        plhs[0] = convertPtr2Mat<XlsStream>(new XlsStream);
        return;
    }

    /* Destructor */
    if(!strcmp("pss", cmd)) 
    {
        destroyObject<XlsStream>(prhs[1]);
        return;
    }

    // Get instance pointer from the second input
    XlsStream *xlsstream_instance = convertMat2Ptr<XlsStream>(prhs[1]);
  
  	/* saveXls() */
    if(!strcmp("saveXls", cmd)) 
    {
        xlsstream_instance->saveXls();
        return;
    }

    /* fromXlsx(std::string) */
    if(!strcmp("fromXlsx", cmd))
    {
    	char* path = cstrFromMx(prhs[1]);
	    xlsstream_instance->fromXlsx(path);
        return;
    }

    mxFree(cmd);

}