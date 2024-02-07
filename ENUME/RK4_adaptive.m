clear all;
close all;

% Set initial conditions and time span
initial_conditions = [0; -0.4];
t_span = [0, 15];

% Set the initial step size
h = 0.001; % Adjust as needed

% Set tolerance for error estimation
tolerance = 1e-6;

% Initialize arrays to store results
t_values = t_span(1):h:t_span(2);
y_values = zeros(length(initial_conditions), length(t_values));

% Perform RK4 integration with variable step size
y_values(:,1) = initial_conditions;
for i = 1:(length(t_values)-1)
    t = t_values(i);
    y = y_values(:,i);
    
    % Use RK4 to calculate the state at the next step
    k1 = h * system(t, y);
    k2 = h * system(t + 0.5*h, y + 0.5*k1);
    k3 = h * system(t + 0.5*h, y + 0.5*k2);
    k4 = h * system(t + h, y + k3);
    y_next = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
    
    % Use step-doubling to estimate error
    k1_double = h * system(t, y);
    k2_double = h * system(t + h, y + k1_double);
    y_double = y + (k1_double + k2_double) / 2; % Double step size
    error = norm((k1_double - k2_double) / 6);
    
    % Adjust step size based on error
    if error < tolerance
        y_values(:,i+1) = y_next;
    else
        h = 0.9 * h * (tolerance / error)^(1/4); % Adjusted step size
        t_values = [t_values(1:i), t_values(i) + h, t_values(i+1:end)];
        y_values = [y_values(:,1:i), y_next, y_values(:,i+1:end)];
    end
end

% Plot the results
figure;
subplot(2, 1, 1);
plot(t_values, y_values(1,:), 'b', t_values, y_values(2,:), 'r');
title('RK4 Solution with Adaptive Step Size');
xlabel('Time');
ylabel('State Variables');
legend('x1', 'x2');

% Plot x2 versus x1
subplot(2, 1, 2);
plot(y_values(1,:), y_values(2,:), 'k');
title('Phase Portrait: x2 vs x1');
xlabel('x1');
ylabel('x2');
grid on;

% Display the final values
disp('Final values at t = 15:');
disp(['x1: ', num2str(y_values(1, end))]);
disp(['x2: ', num2str(y_values(2, end))]);

% Define the system of ODEs
function dydt = system(t, y)
    dydt = [y(2) + y(1)*(0.5 - y(1)^2 - y(2)^2); 
            -y(1) + y(2)*(0.5 - y(1)^2 - y(2)^2)];
end
