% Mouse - Matlab wrapper class
classdef mouse < handle
    properties
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        % Constructor 
        function this = mouse(row)
            this.objectHandle = mouse_mex('new',row.objectHandle);
        end
        
        % Destructor
        function delete(this)
            mouse_mex('delete', this.objectHandle);
        end

        % get trigger data as cell array
        function t = trig(this)
            t = mouse_mex('trig', this.objectHandle);
        end

        % get trigger data as cell array
        function r = rand(this)
            r = mouse_mex('rand', this.objectHandle);
        end

        % get mouse private  data as cell array
        function result = data(this)
            result = mouse_mex('data', this.objectHandle);
        end
    end
end