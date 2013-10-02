%XlsStream
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
        function varargout = saveXls(this, varargin)
            [varargout{1:nargout}] = xlsstream_mex('saveXls', this.objectHandle, varargin{:});
        end

        %% fromXlsx
        function varargout = fromXlsx(this, varargin)
            [varargout{1:nargout}] = xlsstream_mex('fromXlsx', this.objectHandle, varargin{:});
        end
    end
end