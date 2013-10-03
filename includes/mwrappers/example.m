clear

xlsapp = xlsstream;
xlsapp.fromXlsx('PeakDetector.xlsx');
sheet = xlsapp.getSheet('1');
header = sheet.getRow('0');
row = sheet.getRow('1');

xlsapp2 = xlsstream;
sheet2 = xlsworksheet;
xlsapp2.addWorksheet(sheet2);
sheet2.addRow(header);
m = mouse(row);

r = xlsrow;
d = m.data;
r.addCellsFromStrings(d);

xlsapp2.saveXls('test.xls');

% sheet 0 = 40Hz unscored
% sheet 1 = 40Hz SWS
% sheet 2 = 
% sheet 4 = 
% ...it appears that the sheets are in reverse order. Maybe fix this?

t = m.trig();
r = m.rand();

sizen = row.numel();
sizet = numel(t);
sizer = numel(r);

% loop through trigger values
for i=1:sizet
	value = t(i);

	% are we greater than 0
	if value>0
		if ((i>20) && (i<(sizet-20)))
			neighborhood = t(i-20:i+20);
			largest = max(neighborhood);

			% are we greater than (or equal to) surrounding neighborhood (i.e. local maxima)
			if value >= largest

				% check slope  (might be redundant)
				slopefwd  = (value-t(i-20))/20;
				slopebkwd = (t(i+20)-value)/20;
				if(slopefwd > 0 && slopebkwd < 0)
					% disp(value);
				end
			end
		end

	% are we less than 0
	elseif value<0
		if ((i>20) && (i<(sizet-20)))
			neighborhood = t(i-20:i+20);
			largest = max(neighborhood);

			% are we less than (or equal to) surrounding neighborhood (i.e. local minima)
			if value >= largest
				
				% check slope (might be redundant)
				slopefwd  = (value-t(i-20))/20;
				slopebkwd = (t(i+20)-value)/20;
				if(slopefwd < 0 && slopebkwd > 0)
					% disp(value);
				end

			end
		end
	end
end


