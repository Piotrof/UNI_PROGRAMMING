clear all;
clc

part_a();

%generate a matrix according to the instruction in a)
function matrix = gen_matrix_a(n)
    matrix(n,n) = zeros;

    for i = 1:n
        for j = 1:n
            if i == j
                matrix(i,j) = 13;
            elseif i == j - 1 || i == j + 1
                matrix(i,j) = 4;
            else
                matrix(i,j) = 0;
            end
        end
    end
end

%generate a vector according to the instruction in a)
function [vector] = gen_vector_a(n)
    vector = zeros([n 1]);
    for i = 1:n
        vector(i) = 2.4 + 0.6 * i;
    end
end

%generate a matrix according to the instruction in b)
function matrix = gen_matrix_b(n)
    matrix(n,n) = zeros;

    for i = 1:n
        for j = 1:n
            matrix(i,j) = 4 / (5 * (i + j -1));
        end
    end
end

%generate a vector according to the instruction in b)
function [vector] = gen_vector_b(n)
    vector = zeros([n 1]);
    for i = 1:n
        vector(i) = 1 / 2 * i;
    end
end

%solve the system of equations by Gaussian elim. with partial pivoting
function [U, b] = to_upper_triangular(A, b)
    [n, m] = size(A);
    
    augmentedMatrix = [A, b];
    
    for k = 1:n
        % Partial pivoting
        [~, maxRow] = max(abs(augmentedMatrix(k:n, k)));
        maxRow = maxRow + k - 1;
        augmentedMatrix([k, maxRow], :) = augmentedMatrix([maxRow, k], :);
        
        % Elimination process
        for i = k+1:n
            factor = augmentedMatrix(i, k) / augmentedMatrix(k, k);
            augmentedMatrix(i, k:n+1) = augmentedMatrix(i, k:n+1) - factor * augmentedMatrix(k, k:n+1);
        end
    end
    
    U = augmentedMatrix(:, 1:n);
    b = augmentedMatrix(:, n+1);
end

function solution = backward_substitution(U, b)
    [n, ~] = size(U);
    solution = zeros(n, 1);
    
    for i = n:-1:1
        solution(i) = (b(i, 1) - U(i, i+1:n) * solution(i+1:n)) / U(i, i);
    end
end

%calculate solution error
function err_norm = calc_error(matrix, vector, solution_vector,n)
    err_vec = matrix * solution_vector - vector;
    err_norm = norm(err_vec);
    if n == 10
    disp(err_norm);
    end
end

%perform residual correction
function res_corr(matrix, vector, solution_vector, error_norm)
   
    x0 = solution_vector;
    alpha = 0.1;
    treshold = 1e-16;
    r = 1;
    while r > treshold
         r = vector - matrix * x0;
         x0 = x0 + alpha * r;
    end
    disp("Performing residual correction");
    disp("Corrected solution: ")
    disp(x0);
end

%part a) of the task
function part_a(~)
    %set the initial no. of equations
    n = 10;
    %set no. of iterations
    it = 5;
    %init. a vector for the calculated errors
    err_vec = zeros([1 it]);
    n_vec = zeros([1 it]);

    for i = 1:it
        if n == 10 %case for the first set of equations
            A = gen_matrix_a(n);
            b = gen_vector_a(n);
            disp("Initial matrix:");
            disp(A);
            disp("Initial vector:");
            disp(b);
            [U, b] = to_upper_triangular(A,b);
            res = backward_substitution(U,b);
            disp('Results for n = 10:');
            disp(res); 
            disp("Error norm for n = 10:");
            err_vec(i) = calc_error(U,b,res,n);
            n_vec(i) = n;
            disp("Results obtained using A\b:");
            disp(A\b);
            res_corr(A, b, res, err_vec(i));
            disp("Condition no. for matrix A:");
            disp("It:");
            disp(i);
            disp(cond(A));
        else %for values of n different than 10
            A = gen_matrix_a(n);
            b = gen_vector_a(n);
            [U, b] = to_upper_triangular(A,b);
            res = backward_substitution(U,b);
            err_vec(i) = calc_error(U,b,res,n);
            n_vec(i) = n;
            disp("Condition no. for matrix A:");
            disp("It:");
            disp(i);
            disp(cond(A));
        end
        n = n * 2;
    end
    plot(n_vec,err_vec,'--*');
    title('Solution error vs. number of equations');
    xlabel('No. of equations');
    ylabel('Solution error');
end

%part b) of the task
function part_b(~)
%set the initial no. of equations
    n = 10;
    %set no. of iterations
    it = 5;
    %init. a vector for the calculated errors
    err_vec = zeros([1 it]);
    n_vec = zeros([1 it]);

    for i = 1:it
        if n == 10 %case for the first set of equations
            A = gen_matrix_b(n);
            b = gen_vector_b(n);
            disp("Initial matrix:");
            disp(A);
            disp("Initial vector:");
            disp(b);
            [U, b] = to_upper_triangular(A,b);
            res = backward_substitution(U,b);
            disp('Results for n = 10:');
            disp(res); 
            disp("Error norm for n = 10:");
            err_vec(i) = calc_error(U,b,res,n);
            n_vec(i) = n;
            disp("Results obtained using A\b:");
            disp(A\b);
            res_corr(A, b, res, err_vec(i));
            disp("Condition no. for matrix A:");
            disp("It:");
            disp(i);
            disp(cond(A));
        else %for values of n different than 10
            A = gen_matrix_b(n);
            b = gen_vector_b(n);
            [U, b] = to_upper_triangular(A,b);
            res = backward_substitution(U,b);
            err_vec(i) = calc_error(U,b,res,n);
            n_vec(i) = n;
            disp("Condition no. for matrix A:");
            disp("It:");
            disp(i);
            disp(cond(A));
        end
        n = n * 2;
    end
    plot(n_vec,err_vec,'--*');
    title('Solution error vs. number of equations');
    xlabel('No. of equations');
    ylabel('Solution error');

    disp("Condition no. for matrix A:");
    disp(cond(A));
end
