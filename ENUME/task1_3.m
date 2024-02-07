clc 
clear;
fplot(@(x) F(x));
grid on;
title("F(x)");
xlabel("x");
ylabel("F(x)");

fprintf("Solutions for MM1 \n");
fprintf("First two zeros for x0=-5 x1=-4.8 x2=-4.7\n");
mm1root1 = MM1(-5,-4.8,-4.7, 1e-12,100); 
fprintf("\nThird zero for x0=-1 x1=-0.8 x2=-0.6\n");
mm1root2 = MM1(-1,-0.8,-0.6, 1e-12,100);  
fprintf("\nFourth zero for x0=10.3i x1=1+0.5i x2=1+1i\n")
mm1root4 = MM1(10, 1+0.5i, 1+11, 1e-12, 100);

fprintf("Solutions for MM2 \n");
fprintf("First zero for x0 = 6 \n");
mm2root1 = MM2(6,1e-12,100); 
fprintf("\nSecond zero for x0 = -0.5 \n");
mm2root2 = MM2(-0.5, 1e-12,100); 
fprintf("\nThird and Fourth zeros for x0 = 1(+/-)0.3i \n") 
mm2root3 = MM2(1-0.3i, 1e-12, 10);  

fprintf("\nReal solutions for Newton's \n");
fprintf("First zero for x0 = 6\n");
nroot1 = Newtons(6);
fprintf("Second zero for x0 = -0.5\n");
nroot2 = Newtons(-0.5);

fprintf("\nSolutions for Laguerre's\n");
fprintf("First zero for x0 = 6\n");
lroot1 = Laguerres(6,1e-12,100);
fprintf("\nSecond zero for x0 = -0.5 \n");
lroot2 = Laguerres(-0.5, 1e-12,100); 
fprintf("\nThird and Fourth zeros for x0 = 1(+/-)0.3i \n") 
lroot3 = Laguerres(1-0.3i, 1e-12, 10); 

function y = F(x)
    y = -2*x^4+12*x^3+4*x^2+x+3;
end
