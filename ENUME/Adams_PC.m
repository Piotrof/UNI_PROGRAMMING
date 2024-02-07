close all;
clear all;

% Set initial conditions and time span
initial_conditions = [0; -0.4];
t_span = [0, 15];

% Set the step size
h = 0.01; % Adjust as needed

% Initialize arrays to store results
t_values = t_span(1):h:t_span(2);
y_values_adams_pc = zeros(length(initial_conditions), length(t_values));

% Perform Adams PC integration
y_values_adams_pc(:,1) = initial_conditions;

% Use RK4 to get the first few steps
for i = 1:4
    y_values_adams_pc(:,i+1) = rk4_step(t_values(i), y_values_adams_pc(:,i), h);
end

% Use Adams PC for the rest of the steps
for i = 5:(length(t_values)-1)
    predictor = y_values_adams_pc(:,i) + h/24 * (55 * system(t_values(i), y_values_adams_pc(:,i)) - 59 * system(t_values(i-1), y_values_adams_pc(:,i-1)) + 37 * system(t_values(i-2), y_values_adams_pc(:,i-2)) - 9 * system(t_values(i-3), y_values_adams_pc(:,i-3)));
    corrector = y_values_adams_pc(:,i) + h/24 * (9 * system(t_values(i+1), predictor) + 19 * system(t_values(i), y_values_adams_pc(:,i)) - 5 * system(t_values(i-1), y_values_adams_pc(:,i-1)) + system(t_values(i-2), y_values_adams_pc(:,i-2)));
    y_values_adams_pc(:,i+1) = corrector;
end

% Plot the results
figure;
subplot(2, 1, 1);
plot(t_values, y_values_adams_pc(1,:), 'b', t_values, y_values_adams_pc(2,:), 'r');
title('Adams PC Solution');
xlabel('Time');
ylabel('State Variables');
legend('x1', 'x2');

% Plot x2 versus x1
subplot(2, 1, 2);
plot(y_values_adams_pc(1,:), y_values_adams_pc(2,:), 'k');
title('Phase Portrait: x2 vs x1 (Adams PC)');
xlabel('x1');
ylabel('x2');
grid on;

% Display the final values
disp('Final values at t = 15:');
disp(['x1: ', num2str(y_values_adams_pc(1, end))]);
disp(['x2: ', num2str(y_values_adams_pc(2, end))]);
disp(['Step-size h : ',num2str(h)]);

% Define the system of ODEs
function dydt = system(t, y)
    dydt = [y(2) + y(1)*(0.5 - y(1)^2 - y(2)^2); 
            -y(1) + y(2)*(0.5 - y(1)^2 - y(2)^2)];
end

% Implement the RK4 method
function yout = rk4_step(t, y, h)
    k1 = h * system(t, y);
    k2 = h * system(t + 0.5*h, y + 0.5*k1);
    k3 = h * system(t + 0.5*h, y + 0.5*k2);
    k4 = h * system(t + h, y + k3);
    yout = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
end
