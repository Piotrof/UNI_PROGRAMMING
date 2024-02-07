close all;clear all;

transforms = zeros(100);

for i = 1:100
    transforms(i) = fft(f(i));
end

plot(transforms);
xlabel("n");
ylabel("transform @ n");

function y = f(n)
    if (10 <= n) && (n <= 49)
        y = sin(90*n);
    else
        y = 0;
    end
end