%===========================================================================
%
% EXAMPLE
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
sheet = xlsapp.getSheet('13');
numrows = 60;

% create the new header
sheet2 = xlsworksheet;
header = sheet.getRow('0');
cells = header.cells;
newHeader = cells(1:7);
newHeader{end+1} = 'Trig-Max-Time';
newHeader{end+1} = 'Trig-Max-Potential';
newHeader{end+1} = 'Trig-Min-Time';
newHeader{end+1} = 'Trig-Min-Potential';
newHeader{end+1} = 'Rand-Max-Time';
newHeader{end+1} = 'Rand-Max-Potential';
newHeader{end+1} = 'Rand-Min-Time';
newHeader{end+1} = 'Rand-Min-Potential';

r = xlsrow;
r.addCellsFromStrings(newHeader);
sheet2.addRow(r);

rows = {};

% loop through the rows and create the max/min data
for k=1:numrows

	% for every row, create a new 'mouse' object
	row = sheet.getRow(num2str(k));
	m = mouse(row);

	% create some arrays to hold the data
	randmax = {};
	randmin = {};
	trigmax = {};
	trigmin = {};

	% loop through rand/trig
	sections = { m.trig, m.rand };
	for n=1:2, section = sections{n};

		% loop through section (rand or trigger) values
		for i=1:numel(section)
			value = section(i);

			% are we greater than 0?
			if value>0
				if ((i>20) && (i<(numel(section)-20)))
					neighborhood = section(i-20:i+20);
					largest = max(neighborhood);

					% are we greater than or equal to the values in the surrounding neighborhood? (i.e. local maxima)
					if value >= largest
						if mod(n,2) 
							trigmax{end+1} = value;
							trigmax_time = header.cells{8+i};
						else 
							randmax{end+1} = value;
							randmax_time = header.cells{408+i};
						end
					end
				end

			% are we less than 0?
			elseif value<0
				if ((i>20) && (i<(numel(section)-20)))
					neighborhood = section(i-20:i+20);
					largest = min(neighborhood);

					% are we less than or equal to the values in the surrounding neighborhood? (i.e. local minima)
					if value <= largest
						if mod(n,2) 
							trigmin{end+1} = value;
							trigmin_time = header.cells{8+i};

						else 
							randmin{end+1} = value;
							randmin_time = header.cells{408+i};
						end
					end
				end
			end % end 'are we less/greater than 0?'
		end % end 'loop through values'
	end % end 'loop through rand/trig'

	% find max
	trigmax_time = strsplit(trigmax_time,' ');
	trigmin_time = strsplit(trigmin_time,' '); 
	randmax_time = strsplit(randmax_time,' ');
	randmin_time = strsplit(randmin_time,' ');
	trigmax = max(cellfun(@(x) x, trigmax));
	trigmin = max(cellfun(@(x) x, trigmin));
	randmax = max(cellfun(@(x) x, randmax));
	randmin = max(cellfun(@(x) x, randmin));

	% create row from data and append to the worksheet
	rowdata = m.data;
	rowdata{end+1} = trigmax_time{end};
	rowdata{end+1} = num2str(trigmax);
	rowdata{end+1} = trigmin_time{end};
	rowdata{end+1} = num2str(trigmin);
	rowdata{end+1} = randmax_time{end};
	rowdata{end+1} = num2str(randmax);
	rowdata{end+1} = randmin_time{end};
	rowdata{end+1} = num2str(randmin);
	rows{end+1} = xlsrow;
	rows{end}.addCellsFromStrings(rowdata);
	sheet2.addRow(rows{end});

end % end 'loop though rows'

% open and initialize the second excel doc (output)
xlsapp2 = xlsstream;
xlsapp2.addWorksheet(sheet2);
xlsapp2.saveXls('test.xls');
disp('done');
