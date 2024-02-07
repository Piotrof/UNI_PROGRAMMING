A = [1 2 6 7 4; 
     2 1 3 7 4;
     6 3 1 4 8;
     7 7 4 1 5;
     4 4 8 5 1];
A = A + A';
disp("Starting matrix:");
disp(A);
threshold = 1e-6;

qr_method_no_shifts(A,threshold);
qr_method_with_shifts(A,threshold);

function [Q, R] = my_qr(A)
    [m, n] = size(A);
    if (m > n)
% Initialization
R = zeros(m,n);
Q = eye(m,m);
z = zeros(m);
    for j = 1:n
        % Reflection of column vector of A
        y = A(j:end,j);
        w = y +sign(A(j,j))*norm(y)*eye(size(y,1),1);
        v = w/norm(w);
        Dummy = 2*(v*v');
        z(j:end,j:end) = Dummy;
        % Generating Househoulder Matrix
        H = eye(m) - z;
        % Calculating new matrix A using H*A
        A = H*A;
        % Calculating orthogonal matrix, Q using Q=H1*H2*....*Hn
        Q = Q*H;
        z = zeros(m);
    end
  
    else
% Initialization
R = zeros(m,n);
Q = eye(m,m);
z = zeros(m);
    for j = 1:m-1
        % Reflection of column vector of A
        y = A(j:end,j);
        w = y +sign(A(j,j))*norm(y)*eye(size(y,1),1);
        v = w/norm(w);
        Dummy = 2*(v*v');
        z(j:end,j:end) = Dummy;
        % Generating Househoulder Matrix
        H = eye(m) - z;
        % Calculating new matrix A using H*A
        A = H*A;
        % Calculating orthogonal matrix, Q using Q=H1*H2*....*Hn
        Q = Q*H;
        z = zeros(m);
    end
    end
% Forming the R matrix, R = A
    for i = 1:m
        for j = i:n
            R(i,j) = A(i,j);
        end
    end
end

function eigenvalues = my_eig(A, max_iterations)
    % Check if the input matrix A is square
    [m, n] = size(A);
    if m ~= n
        error('Input matrix must be square.');
    end
    
    % Set default maximum number of iterations if not provided
    if nargin < 2
        max_iterations = 1000;
    end

    % Initialize eigenvalues vector
    eigenvalues = zeros(1, n);

    % Apply the QR algorithm
    for k = 1:max_iterations
        [Q, R] = my_qr(A);
        A = R * Q;
    end

    % Extract eigenvalues from the diagonal of the final matrix
    eigenvalues = diag(A);
end

function qr_method_no_shifts(A, threshold)
    % QR method without shifts
    
    % Check if the matrix is square
    [m, n] = size(A);
    if m ~= n
        error('Input matrix must be square.');
    end
    
    % Initialize iteration counter
    iterations = 0;
    
    % Perform QR method until all off-diagonal elements are below the threshold
    while max(max(abs(triu(A, 1)))) > threshold
        [Q, R] = my_qr(A);
        A = R * Q;
        iterations = iterations + 1;
    end
    
    % Display results
    fprintf('Number of iterations: %d\n', iterations);
    fprintf('Final Matrix:\n');
    disp(A);
end

function qr_method_with_shifts(A, threshold)
    % QR method with shifts based on the eigenvalue of the 2x2 lower right corner submatrix
    
    % Check if the matrix is square
    [m, n] = size(A);
    if m ~= n
        error('Input matrix must be square.');
    end
    
    % Initialize iteration counter
    iterations = 0;
    
    % Perform QR method with shifts until all off-diagonal elements are below the threshold
    while max(max(abs(triu(A, 1)))) > threshold
        % Compute Wilkinson shift
        mu = wilkinson_shift(A);
        
        % Apply shifted QR decomposition
        [Q, R] = my_qr(A - mu * eye(size(A)));
        A = R * Q + mu * eye(size(A));
        
        iterations = iterations + 1;
    end
    
    % Display results
    fprintf('Number of iterations: %d\n', iterations);
    fprintf('Final Matrix:\n');
    disp(A);
end

function mu = wilkinson_shift(A)
    % Compute Wilkinson shift for a 5x5 matrix based on the eigenvalue of the 2x2 lower right corner submatrix
    
    % Extract the 2x2 lower right corner submatrix
    B = A(end-1:end, end-1:end);
    
    % Compute eigenvalues of B
    eigvals = my_eig(B);
    disp("Eigvals obtained thorugh the algorithm:");
    disp(eigvals);
    disp("Eigvals obtained through the built-in function:");
    disp(eig(B));
    % Choose the eigenvalue closer to the diagonal element
    if abs(B(2, 2) - eigvals(1)) < abs(B(2, 2) - eigvals(2))
        mu = eigvals(1);
    else
        mu = eigvals(2);
    end
end
