function kernel_invocations_syrk(A, C, b)

reps = str2num(getenv('LAMP_REPS'));

implicit_syrk_ = @() implicit_syrk(A, C);
syrk_implicit_noup_ = @() syrk_implicit_noup(A);

b.benchmark("syrk_implicit", reps, implicit_syrk_);
b.benchmark("syrk_implicit_noup", reps, syrk_implicit_noup_);
end

function [C, time] = implicit_syrk(A, C)
tic;
C = A*A' + C;
time = toc;
end

function [C, time] = syrk_implicit_noup(A)
tic;
C = A*A';
time = toc;
end
