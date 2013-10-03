% XlsStream - Matlab wrapper class
classdef xlsstream < handle
    properties
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        % Constructor 
        function this = xlsstream()
            this.objectHandle = xlsstream_mex('new');
        end
        
        % Destructor
        function delete(this)
            xlsstream_mex('delete', this.objectHandle);
        end

        % saveXls
        function saveXls(this, varargin)
            xlsstream_mex('saveXls', this.objectHandle, varargin{:});
        end

        % fromXlsx
        function varargout = fromXlsx(this, varargin)
            xlsstream_mex('fromXlsx', this.objectHandle, varargin{:});
        end

        % getSheet
        function wsheet = getSheet(this, varargin)
            ptr = xlsstream_mex('getSheet', this.objectHandle, varargin{:});
            wsheet = xlsworksheet();
            wsheet.setHandle(ptr);
        end

        % addWorksheet
        function addWorksheet(this, sheet)
            xlsstream_mex('addWorksheet', this.objectHandle, sheet.objectHandle);
            % wsheet = xlsworksheet;
            % wsheet.setHandle(ptr);
        end
    end
end