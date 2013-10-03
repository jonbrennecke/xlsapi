#include "includes/mouse/mouse.h"
#include "includes/sys/sys.hpp"
#include "includes/xlsapi/xlsapi.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T, size_t N> const T* mybegin(const T (&a)[N]) { return a; }    
template <typename T, size_t N> const T* myend  (const T (&a)[N]) { return a+N; }

int main(int argc, char *argv[])
{
	XlsStream *xlsApp = new XlsStream();
	xlsApp->fromXlsx("PeakDetector.xlsx");
	xlsApp->saveXls("testsave.xls");

	/*	loop through rows of the 1st sheet
	*	skipping the first row
	* 
	*	for some reason the worksheets come out in unpredictable order
	*	so we'll need to implement a method to organize these 
	*/

	// XlsRow* row = xlsApp->worksheets[1]->rows[1];
	// Mouse* mouse = new Mouse(row);


	// for(int i=0;i<mouse->trig.size();i++)
	// {
	// 	float t = mouse->trig[i];
	// 	if(t<=0) continue; // are we greater than zero?
	// 	if(i>20 && i<(mouse->trig.size()-20)){

	// 		std::vector<float>::const_iterator first = mouse->trig.begin() + i-20;
	// 		std::vector<float>::const_iterator last = mouse->trig.begin() + i+20;
	// 		std::vector<float>::const_iterator mid = mouse->trig.begin() + i;
	// 		// std::vector<float> subsection(first, last);

	// 		float max = *std::max_element(first,last);
	// 		if(t>=max)
	// 		{
	// 			// max of 20 surrounding values
	// 		}





	// 		// for(int j=0;j<sub.size();j++)
	// 		// {
	// 		// 	if()
	// 		// }

	// 		// const float[] before = mouse->trig[i-20]
	// 		// for(int j=i-20;j<i+20;j++) // greater than surrounding neighborhood? (+- 20 values)
	// 		// {
	// 		// 	// if()
	// 		// }
	// 	}
	// }



	// for(int i=1;i<72;i++)
	// {
	// 	XlsRow* row = xlsApp->worksheets[13]->rows[i];
	// 	Mouse* mouse = new Mouse(row);
	// }

	return 0;
}