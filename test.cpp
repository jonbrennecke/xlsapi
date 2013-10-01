#include "includes/mouse/mouse.h"
#include "includes/sys/sys.hpp"
#include "includes/xlsapi/xlsapi.h"
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char *argv[])
{
	XlsStream *xlsApp = new XlsStream();
	xlsApp->fromXlsx("PeakDetector.xlsx");

	/*	loop through rows of the 1st sheet
	*	skipping the first row
	* 
	*	for some reason the worksheets come out in unpredictable order
	*	so we'll need to implement a method to organize these 
	*/

	XlsRow* row = xlsApp->worksheets[13]->rows[1];
	Mouse* mouse = new Mouse(row);


	for(int i=0;i<mouse->trig.size();i++)
	{
		float t = mouse->trig[i];
		if(t<=0) break; // are we greater than zero?
		if(i>20 && i<(mouse->trig.size()-20)){
			for(int j=i-20;j<i+20;j++) // greater than surrounding neighborhood? (+- 20 values)
			{
				if()
			}
		}
	}



	// for(int i=1;i<72;i++)
	// {
	// 	XlsRow* row = xlsApp->worksheets[13]->rows[i];
	// 	Mouse* mouse = new Mouse(row);
	// }

	return 0;
}