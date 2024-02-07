function x = Laguerres(x, tolerance, iterations)
n = 4; 
for i = 1:iterations
    if abs(f(x)) > tolerance
        root = sqrt((n-1)*((n-1)*(df(x))^2 - n*f(x)*ddf(x)));
        if abs(df(x) + root) > abs(df(x) - root)
            xk = x - (n*f(x)) /(df(x) + root);
        else 
            xk = x - (n*f(x)) /(df(x) - root );
        end 
        x = xk; 
        fprintf("%d iteration x = %f+%fi f(x) = %f\n", i, real(xk), imag(xk), f(xk)); 
    else 
        break; 
    end 
end 
end 

function y = f(x) 
    y = -2*x^4 + 12*x^3 + 4*x^2 + x + 3; 
end 

function y = df(x) 
    y = -8*x^3 + 36*x^2 + 8*x + 1; 
end

function y = ddf(x) 
    y = -24*x^3 + 72*x + 8; 
end 

