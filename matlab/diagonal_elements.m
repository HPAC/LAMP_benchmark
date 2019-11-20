function diagonal_elements(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

implicit_mult_ = @() implicit_mult(A, B);
implicit_ = @() implicit(A, B);
explicit_ = @() explicit(A, B);

b.benchmark('diag_mult_nai', reps, implicit_mult_);
b.benchmark('diag_add_nai', reps, implicit_);
b.benchmark('diag_add_rec', reps, explicit_);
end

function [C, time] = implicit_mult(A, B)
tic;
C = diag(A * B);
time = toc;
end

function [C, time] = implicit(A, B)
tic;
C = diag(A + B);
time = toc;
end

function [C, time] = explicit(A, B)
tic;
C = diag(A) + diag(B);
time = toc;
end
