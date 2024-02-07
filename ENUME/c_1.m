clear all;
close all;

% Experimental data
x = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5];
y = [-34.5986, -18.2300, -8.5370, -1.9635, 0.5497, 2.7879, 2.7176, 3.3830, 6.3024, 12.2910, 23.2003];

% Define the degrees of polynomials to test
degrees = 10;

lambda = 0.1; % Ridge regularization parameter (adjust as needed)

for degree = 1:degrees
    % Construct the matrix A for the current degree using orthogonal polynomials
    A = zeros(length(x), degree + 1);
    for i = 1:degree + 1
        A(:, i) = legendreP(degree, x')'; % Example: Legendre polynomial as orthogonal basis
    end

    % Normalize the matrix A
    A_normalized = zscore(A);

    % Display the condition number of the Gram's matrix
    fprintf('Polynomial Degree: %d\n', degree);
    fprintf('Condition Number of Gram''s Matrix: %f\n', cond(A_normalized' * A_normalized));

    % Ridge regression (L2 regularization)
    I = eye(degree + 1);
    a = (A_normalized' * A_normalized + lambda * I) \ (A_normalized' * y');

    % Evaluate the polynomial using the obtained coefficients
    fitted_y_ridge = polyval(a, x);

    % Calculate the error using the Euclidean norm
    error_ridge = norm(y - fitted_y_ridge);

    % Display or store the results
    fprintf('Error (Ridge Regression): %f\n\n', error_ridge);

    % Plot the results
    figure;
    plot(x, y, 'o', 'DisplayName', 'Experimental Data');
    hold on;
    plot(x, fitted_y_ridge, 'g--', 'DisplayName', 'Ridge Regression Solution');
    xlabel('x');
    ylabel('y');
    title(['Polynomial Fit Comparison (Degree ' num2str(degree) ')']);
    legend('show');
    hold off;
end
