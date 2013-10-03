#include "../../mex/mex.h"
#include "../../xlsapi/xlsapi.h"
#include "../../mouse/mouse.h"
#include "mexutils.hpp"
#include <string>
#include <stdio.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	char* cmd = cstrFromMx(prhs[0]);

    /* Constructor */
    if(!strcmp("new", cmd))
    {
        XlsRow* row = convertMat2Ptr<XlsRow>(prhs[1]);

        // Return a handle to a new C++ instance
        Mouse *mouse = new Mouse(row);
        plhs[0] = convertPtr2Mat<Mouse>(mouse);
        return;
    }

    /* Destructor */
    if(!strcmp("delete", cmd)) 
    {
        destroyObject<Mouse>(prhs[1]);
        return;
    }

    // Get instance pointer from the second input
    Mouse *mouse = convertMat2Ptr<Mouse>(prhs[1]);

    /* get the trigger data as a matrix */
    if(!strcmp("trig", cmd)) 
    {
        plhs[0] = mxCreateNumericMatrix(mouse->trig.size(), 1, mxSINGLE_CLASS, mxREAL);
        float * data = (float *) mxGetData(plhs[0]);
        for(int i=0;i<mouse->trig.size();i++)
        {
            data[i] = mouse->trig[i];
        }
        return;
    }

    /* get the random data as a matrix */
    if(!strcmp("rand", cmd)) 
    {
        plhs[0] = mxCreateNumericMatrix(mouse->rand.size(), 1, mxSINGLE_CLASS, mxREAL);
        float * data = (float *) mxGetData(plhs[0]);
        for(int i=0;i<mouse->rand.size();i++)
        {
            data[i] = mouse->rand[i];
        }
        return;
    }

    /* get the private data as a matrix */
    if(!strcmp("data", cmd)) 
    {
        std::vector<char*> info = mouse->getData();
        const char *str[info.size()];
        for(int i=0;i<info.size();i++)
        {
            str[i] = info[i];
        }
        plhs[0] = mxCreateCharMatrixFromStrings(info.size(), (const char **)str);
        return;
    }

    /* get the private data as a matrix */
    if(!strcmp("data2", cmd)) 
    {
        std::vector<char*> info = mouse->getData();
        const char *str[info.size()];
        const mwSize ndim=1, dims[]={info.size()}; 
        mxArray *mx = mxCreateCellArray(ndim,dims);
        for(int i=0;i<info.size();i++) {
            mxArray* value = mxCreateString(info[i]);
            mxSetCell(mx,i,value);
        }
        plhs[0] = mx;
        return;
    }


    mxFree(cmd);

}