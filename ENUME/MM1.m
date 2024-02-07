

function x = MM1(x0, x1, x2, tolerance, iterations) 
z1 = x1 - x0; 
z2 = x2 - x1; 
d1 = (f(x1) - f(x0))/z1; 
d2 = (f(x2) - f(x1))/z2; 
delta = (d2 - d1)/(z2 + z1); 
for i = 1:iterations 
    b = d2 + z2*delta; 
    root = sqrt(b^2 - 4*f(x2)*delta); 
    if abs(b-root) <= abs(b+root) 
        Z = b + root; 
    else 
        Z = b - root; 
    end 
    z = -2*f(x2)/Z; 
    % New x3 for the next iteration 
    x3 = x2 + z; 
    fprintf("%d-th iteration x = %f+%fi f(x) = %f\n", i, real(x3), imag(x3), f(x3)); 
    if abs(z) < tolerance 
        x=x3; 
        break; 
    end 
    x0 = x1; 
    % New x0, xl, x2
    x1 = x2;
    x2 = x3; 
    z1 = x1 - x0; 
    z2 = x2 - x1; 
    d1 = (f(x1) - f(x0))/z1; 
    d2 = (f(x2) - f(x1))/z2; 
    delta = (d2 - d1)/(z2 + z1); 
end 
end

function y = f(x) 
y = -2*x^4+12*x^3+4*x^2+x+3; 
end 