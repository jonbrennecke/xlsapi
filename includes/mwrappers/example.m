%===========================================================================
%
% EXAMPLE OF USING XLSSTREAM MEX WRAPPERS LIBRARY
% 
% code by Jon Brennecke 
% - brennecke.jonathan@wsu.edu
% - http://github.com/jonbrennecke
%
% on linux, or in windows with Cygwin, you can download this project
% by typing in the command line: 
% 	curl -LOk https://github.com/jonbrennecke/xlsapi/archive/master.zip
% or to clone the github repository:
% 	git clone http://github.com/jonbrennecke/xlsapi
%
%===========================================================================

clear

% open and initialize the first excel doc (input)
xlsapp = xlsstream;
xlsapp.fromXlsx('PeakDetector.xlsx');
sheet = xlsapp.getSheet('1');
header = sheet.getRow('0');
row = sheet.getRow('1');

% open and initialize the second excel doc (output)
% xlsapp2 = xlsstream;
% sheet2 = xlsworksheet;
% xlsapp2.addWorksheet(sheet2);

% % create the new header
% cells = header.cells;
% newHeader = cells(1:7);
% newHeader{8} = 'Trig-Max1-Time';
% newHeader{9} = 'Trig-Max1-Potential';
% newHeader{10} = 'Trig-Min1-Time';
% newHeader{11} = 'Trig-Min1-Potential';
% newHeader{12} = 'Trig-Max2-Time';
% newHeader{13} = 'Trig-Max2-Potential';
% newHeader{14} = 'Rand-Max1-Time';
% newHeader{15} = 'Rand-Max1-Potential';
% newHeader{16} = 'Rand-Min1-Time';
% newHeader{17} = 'Rand-Min1-Potential';
% newHeader{18} = 'Rand-Max2-Time';
% newHeader{19} = 'Rand-Max2-Potential';
% r = xlsrow;
% r.addCellsFromStrings(newHeader);
% sheet2.addRow(r);

% % for every row, create a mouse object
% m = mouse(row);
% sizen = row.numel();
% sizet = numel(m.trig);
% sizer = numel(m.rand);

% loop through trigger values
% for i=1:sizet
% 	value = t(i);

% 	% are we greater than 0
% 	if value>0
% 		if ((i>20) && (i<(sizet-20)))
% 			neighborhood = t(i-20:i+20);
% 			largest = max(neighborhood);

% 			% are we greater than (or equal to) surrounding neighborhood (i.e. local maxima)
% 			if value >= largest

% 				% check slope  (might be redundant)
% 				slopefwd  = (value-t(i-20))/20;
% 				slopebkwd = (t(i+20)-value)/20;
% 				if(slopefwd > 0 && slopebkwd < 0)
% 					% disp(value);
% 				end
% 			end
% 		end

% 	% are we less than 0
% 	elseif value<0
% 		if ((i>20) && (i<(sizet-20)))
% 			neighborhood = t(i-20:i+20);
% 			largest = max(neighborhood);

% 			% are we less than (or equal to) surrounding neighborhood (i.e. local minima)
% 			if value >= largest
				
% 				% check slope (might be redundant)
% 				slopefwd  = (value-t(i-20))/20;
% 				slopebkwd = (t(i+20)-value)/20;
% 				if(slopefwd < 0 && slopebkwd > 0)
% 					% disp(value);
% 				end

% 			end
% 		end
% 	end
% end

% xlsapp2.saveXls('test.xls');