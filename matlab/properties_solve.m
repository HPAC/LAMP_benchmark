function properties_solve(m, rhs, b)

reps = str2num(getenv('LAMP_REPS'));

B = randn(m, rhs);

% SPD
A = randn(m, m);
A = A + A' + eye(m)*m;
custom_solve_ = @() custom_solve(A, B);
b.benchmark('solve_spd', reps, custom_solve_);

% Symmetric
A = randn(m, m);
A = A + A'; A(1,1) = -1.0;
custom_solve_ = @() custom_solve(A, B);
b.benchmark('solve_sym', reps, custom_solve_);

% Triangular
A = randn(m, m);
A = tril(A);
custom_solve_ = @() custom_solve(A, B);
b.benchmark('solve_tri', reps, custom_solve_);

% Diagonal
A = randn(m, m);
A = diag(diag(A));
custom_solve_ = @() custom_solve(A, B);
b.benchmark('solve_dia', reps, custom_solve_);

end

function [C, time] = custom_solve(A, B)
tic;
C = A\B;
time = toc;
end

