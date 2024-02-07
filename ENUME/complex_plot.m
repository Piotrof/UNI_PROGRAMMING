clear all;
close all;

a = -2:0.1:7;
b = -2:0.1:2;
[A,B] = meshgrid(a,b);
y = -2*(A+1i*B).^4 + 12*(A+1i*B).^3 + 4*(A+1i*B).^2 + (A+1i*B) + 3;
surfc(a,b,abs(log(y+1)));
title("Complex plot of the polynomial.");
xlabel("Real");
ylabel("Imag");
colormap jet;