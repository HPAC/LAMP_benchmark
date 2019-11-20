% A1 (n,n) A2 (n,n) B (2n, 2n)
function partitioned_matrices(A1, A2, B, b)

reps = str2num(getenv('LAMP_REPS'));

blocked_solve_naive_ = @()       blocked_solve_naive(A1, A2, B);
blocked_solve_recommended_ = @() blocked_solve_recommended(A1, A2, B);

b.benchmark('compact', reps, blocked_solve_naive_);
b.benchmark('blocked', reps, blocked_solve_recommended_);
end

function [C, time] = blocked_solve_naive(A1, A2, B)
tic;
C = [A1 zeros(size(A1,1), size(A1, 2)); zeros(size(A2,1), size(A2, 2)) A2]\B;
time = toc;
end
function [C, time] = blocked_solve_recommended(A1, A2, B)
tic;
b1 = B(1:size(A1, 1), 1:end);
b2 = B(size(A1, 1)+1:end, 1:end);
C = [A1\b1; A2\b2];
time = toc;
end
