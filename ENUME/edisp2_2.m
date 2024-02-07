% Signal (c)
fs = 1024; % Sampling frequency
t = (0:1023) / fs; % Time vector for 1024 points
f1 = 50; % Frequency 1
f2 = 80; % Frequency 2
signal_c = sin(2 * pi * f1 * t) + sin(2 * pi * f2 * t);

% Plot the signal
figure;
subplot(3, 1, 1);
plot(t, signal_c);
title('Signal (c) - Sine Wave');

% Plot the magnitude of FFT
subplot(3, 1, 2);
fft_c = fft(signal_c);
plot(abs(fft_c));
title('Magnitude of FFT - Signal (c)');

% Note the locations of the peaks
[~, idx_peaks] = findpeaks(abs(fft_c), 'SortStr', 'descend');
disp(['Peak locations in FFT - Signal (c): ' num2str(idx_peaks')]);
