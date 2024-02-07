function x = MM2(x, tolerance, iterations)
for i = 1:iterations
    if (abs(f(x)) > tolerance)
        c = f(x);
        b = df(x);
        a = ddf(x); 
        z1 = -2*c/(b+sqrt(b^2-4*a*c));
        z2 = -2*c/(b-sqrt(b^2-4*a*c));
        if abs(b+sqrt(b^2-2*a*c)) > abs(b-sqrt(b^2-2*a*c))
            z_min = z1;
        else
            z_min = z2;
        end
        x = x+z_min;
        fprintf("%d iteration x = %f+%fi f(x) = %f\n", i, real(x), imag(x), f(x));
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


