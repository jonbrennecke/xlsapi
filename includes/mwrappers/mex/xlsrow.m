% XlsRow - Matlab wrapper class
classdef xlsrow < handle
    properties
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        % Constructor 
        function this = xlsrow()
            this.objectHandle = xlsrow_mex('new');
        end
        
        % Destructor
        function delete(this)
            xlsrow_mex('delete', this.objectHandle);
        end

        % set the handle
        function setHandle(this, ptr)
            this.objectHandle = ptr;
        end

        % return the number of elements
        function elem = numel(this)
            elem = xlsrow_mex('numel', this.objectHandle);
        end

        % return the cells as strings
        function elem = cells(this)
            elem = xlsrow_mex('cells', this.objectHandle);
        end

        % return the cells as strings
        function fromStr(this, str)
            xlsrow_mex('fromStr', this.objectHandle, str);
        end
    end
end