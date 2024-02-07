clear all;
close all;

x0 = -5;
[x1, y1] = find_root(x0);
x0 = 10;
[x2, y2] = find_root(x0);

%define f(x)
function y = f(x)
    y = -2.1 + 0.3 * x - x * exp(-x);
end

%define f'(x)
function y = df(x)
    y = 0.3 + x * exp(-x) - exp(-x);
end

%funtion to find the root of f(x) using Newton's method
function [x, y] = find_root(x0)
    
   threshold = 1e-12;
   it = 1;

   fprintf("Finding root, initial guess x0 = %d\n",x0);

   while abs(f(x0)) > threshold
   
       x0 = x0 - (f(x0)/df(x0));
       fprintf("It. no. : %d, root = %f\n",it,x0);
       it = it + 1;
   end 

    x = x0;
    y = f(x0);
end