function kernel_invocations_syr2k(A ,B, C, b)

reps = str2num(getenv('LAMP_REPS'));

syr2k_implicit_ = @() syr2k_implicit(A, B, C);
syr2k_implicit_noup_ = @() syr2k_implicit_noup(A, B);

b.benchmark("syr2k_implicit", reps, syr2k_implicit_);
b.benchmark("syr2k_implicit_noup", reps, syr2k_implicit_noup_);
end

function [C, time] = syr2k_implicit(A, B, C)
tic;
C = A*B'+ B*A' + C;
time = toc;
end

function [C, time] = syr2k_implicit_noup(A, B)
tic;
C = A*B'+ B*A';
time = toc;
end
