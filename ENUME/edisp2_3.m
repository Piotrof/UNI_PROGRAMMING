% Parameters
fs = 1000;   % Sampling frequency in Hz
f = 50;      % Frequency of the sine wave in Hz
N_original = 512; % Original number of samples

% Generate a sine wave
t = (0:N_original-1) * 1/fs;
x = sin(2*pi*f*t);

% FFT for the original 512 samples
X_original = fft(x);

% Zero-pad to 1024 samples
X_1024 = fft(x, 1024);

% Zero-pad to 2048 samples
X_2048 = fft(x, 2048);

% Plotting the results
figure;

% Plot FFT for the original 512 samples
subplot(3, 2, 1);
plot(abs(X_original));
title('FFT for 512 samples');
xlabel('Frequency Bin');
ylabel('Magnitude');

% Plot FFT for 1024 samples
subplot(3, 2, 3);
plot(abs(X_1024));
title('FFT for 1024 samples');
xlabel('Frequency Bin');
ylabel('Magnitude');

% Plot FFT for 2048 samples
subplot(3, 2, 5);
plot(abs(X_2048));
title('FFT for 2048 samples');
xlabel('Frequency Bin');
ylabel('Magnitude');

% Compute IFFT for the original 512 samples and plot real part
subplot(3, 2, 2);
x_original_ifft = ifft(X_original);
plot(real(x_original_ifft));
title('Real part of IFFT for 512 samples');
xlabel('Sample Index');
ylabel('Amplitude');

% Compute IFFT for 1024 samples and plot real part
subplot(3, 2, 4);
x_1024_ifft = ifft(X_1024);
plot(real(x_1024_ifft));
title('Real part of IFFT for 1024 samples');
xlabel('Sample Index');
ylabel('Amplitude');

% Compute IFFT for 2048 samples and plot real part
subplot(3, 2, 6);
x_2048_ifft = ifft(X_2048);
plot(real(x_2048_ifft));
title('Real part of IFFT for 2048 samples');
xlabel('Sample Index');
ylabel('Amplitude');

sgtitle('Comparison of FFT and IFFT with Zero-padding');
