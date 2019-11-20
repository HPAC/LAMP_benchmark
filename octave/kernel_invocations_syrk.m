function kernel_invocations_syrk(A, C, b)

reps = str2num(getenv('LAMP_REPS'));

syrk_implicit_ = @() syrk_implicit(A, C);
syrk_implicit_compact_ = @() syrk_implicit_compact(A, C);
syrk_implicit_noup_ = @() syrk_implicit_noup(A);

b.benchmark("syrk_implicit", reps, syrk_implicit_);
b.benchmark("syrk_implicit_compact", reps, syrk_implicit_compact_);
b.benchmark("syrk_implicit_noup", reps, syrk_implicit_noup_);
end

function [C, time] = syrk_implicit(A, C)
tic;
C = A*A' + C;
time = toc;
end

function [C, time] = syrk_implicit_compact(A, C)
tic;
C += A*A';
time = toc;
end

function [C, time] = syrk_implicit_noup(A)
tic;
C = A*A';
time = toc;
end
