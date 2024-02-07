% Given parameters
T = 2e-3; 
fs = 10e3; 

% (a) Calculate total number of samples (fill in N column) and number of non-zero samples (fill in N1 column):
N = T * fs; % Total number of samples
N1 = 1e-3 * fs; % Number of non-zero samples (1 ms duration)
disp(N);
disp(N1);
% (b) Create a simulated signal in Matlab ([ones(1, N1), zeros(1, N-N1)])
x = [ones(1, N1), zeros(1, N - N1)];

% (c) Calculate with Matlab and plot (on screen) magnitude of FFT (plot(abs(fft(x...))))
X = fft(x);
figure;
plot(abs(X));
title('Magnitude of FFT');
xlabel('Frequency Bin');
ylabel('Magnitude');

% (d) Find the maximum value in FFT (and fill in as Amax)
Amax = max(abs(X));
disp(['Maximum value in FFT: ' num2str(Amax)]);

% (e) Find (and fill in) the index knull of the first null in FFT values
knull = find(abs(X) == min(abs(X(2:end)))) - 1; % Subtract 1 for 0-based indexing
disp(['Index of the first null in FFT values: ' num2str(knull)]);
