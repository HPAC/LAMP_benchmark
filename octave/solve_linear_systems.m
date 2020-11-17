function solve_linear_systems(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

implicit_ = @() implicit(A, B);
explicit_ = @() explicit(A, B);

Bl = randn(size(B,1), 5 * size(A,1));
implicit_large_ = @() implicit(A, Bl);
explicit_large_ = @() explicit(A, Bl);

b.benchmark('solve_nai', reps, implicit_);
b.benchmark('solve_rec', reps, explicit_);

b.benchmark('solve_large_nai', reps, implicit_large_);
b.benchmark('solve_large_rec', reps, explicit_large_);
end

% A warning is at least issued in MATLAB when explicitly writing inv(A)
function [C, time] = implicit(A, B)
tic;
C = inv(A)*B;
time = toc;
end

function [C, time] = explicit(A, B)
tic;
C = A\B;
time = toc;
end
