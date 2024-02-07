clear all;
close all;

[x1, y1] = find_roots(-5, 0);
[x2, y2] = find_roots(0, 10);

function y = f(x)
    y = -2.1 + 0.3*x - x*exp(-x);
end

%function for finding the root of f(x) in an interval
function [x, y] = find_roots(lb, ub)
    
    treshold = 1e-12;
    x0 = lb;
    x1 = ub;
    it = 1;

    if f(x0) * f(x1) > 0
       error("No roots in this interval."); 
    end
    
    A = sprintf('Finding root in interval [%d, %d].',lb,ub);
    disp(A);

    while abs(f(x1)) > treshold
        x2 = x1 - ((f(x1)*(x1 - x0)) / (f(x1) - f(x0)));

        if f(x0) * f(x2) < 0  
            x1 = x2;
        end
        if f(x1) * f(x2) < 0
            x0 = x2;
        end

        B = sprintf('It. no. : %d, root = %f',it,x1);
        disp(B);
        it = it + 1;
    end

    y = f(x1);
    x = x1;
end
