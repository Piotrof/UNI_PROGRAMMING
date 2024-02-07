function x = Newtons(x0)
x = x0;
tolerance=1e-12;
n = 1;

    while abs(f(x)) > tolerance
        x = x - (f(x)/df(x));
        fprintf("%d iteration x = %f f(x) = %f\n",n,x,f(x));
        n = n + 1;
    end
end

function y = f(x) 
y = -2*x^4 + 12*x^3 + 4*x^2 + x + 3; 
end 

function y = df(x) 
y = -8*x^3 + 36*x^2 + 8*x + 1; 
end