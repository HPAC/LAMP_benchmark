function subexpression(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

implicit_ = @() implicit(A, B);
explicit_ = @() explicit(A, B);

b.benchmark('subexpr_nai', reps, implicit_);
b.benchmark('subexpr_rec', reps, explicit_);
end

function [res, time] = implicit(A, B)
tic;
K = A * B + A * B;
time = toc;
res = K;
end

function [res, time] = explicit(A, B)
tic;
K = A * B;
K = K + K;
time = toc;
res = K;
end
