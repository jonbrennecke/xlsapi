% XlsWorksheet - Matlab wrapper class
classdef xlsworksheet < handle
    properties
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        % Constructor 
        function this = xlsworksheet(varargin)
            this.objectHandle = xlsworksheet_mex('new',varargin{:});
        end
        
        % Destructor
        function delete(this)
            xlsworksheet_mex('delete', this.objectHandle);
        end

        % getRow(int)
        function row = getRow(this, varargin)
            ptr = xlsworksheet_mex('getRow', this.objectHandle, varargin{:});
            row = xlsrow;
            row.setHandle(ptr);
        end

        % set the handle
        function setHandle(this, ptr)
            this.objectHandle = ptr;
        end

        % return the number of elements
        function elem = numel(this)
            elem = xlsworksheet_mex('numel', this.objectHandle);
        end

        % add row
        function addRow(this, row)
            xlsworksheet_mex('addRow', this.objectHandle, row.objectHandle);
        end
    end
end