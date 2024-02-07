clear all; 
close all;

% Define the system of ODEs
ode_system = @(t, y) [y(2) + y(1)*(0.5 - y(1)^2 - y(2)^2); 
                      -y(1) + y(2)*(0.5 - y(1)^2 - y(2)^2)];

% Set initial conditions and time span
initial_conditions = [0; -0.4];
t_span = [0, 15];

% Solve the ODE using ode45
[t, y] = ode45(ode_system, t_span, initial_conditions);

% Plot the results
figure;

% Plot x1 and x2 as functions of time
subplot(2, 1, 1);
plot(t, y(:,1), 'b', t, y(:,2), 'r');
title('ODE45 Solution');
xlabel('Time');
ylabel('State Variables');
legend('x1', 'x2');

% Plot x2 versus x1
subplot(2, 1, 2);
plot(y(:,1), y(:,2), 'k');
title('Phase Portrait: x2 vs x1');
xlabel('x1');
ylabel('x2');
grid on;


% Display the final values
disp('Final values:');
disp(['x1: ', num2str(y(end, 1))]);
disp(['x2: ', num2str(y(end, 2))]);