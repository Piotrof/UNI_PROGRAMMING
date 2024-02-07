%calculating the macheps 
calculated_macheps = 1;
while (1.0 + (calculated_macheps/2) > 1.0)

    calculated_macheps = calculated_macheps / 2;

end

%obtaining native macheps value for verification purposes 
native_macheps = eps(1);