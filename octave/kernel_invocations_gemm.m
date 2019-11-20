function kernel_invocations_gemm(A ,B, C, b)

reps = str2num(getenv('LAMP_REPS'));

gemm_implicit_ = @() gemm_implicit(A, B, C);
gemm_implicit_noup_ = @() gemm_implicit_noup(A, B, C);
gemm_implicit_compact_ = @() gemm_implicit_compact(A, B, C);
gemm_implicit_coeff_ = @() gemm_implicit_coeff(A, B, C);
gemm_implicit_double_coeff_ = @() gemm_implicit_double_coeff(A, B, C);

Asy = A * A';
Ad = diag(diag(Asy));
Ad(1,2) = 1.2;
Ad(1,2) = 0.0;
Bsq = randn(size(A, 1), size(A, 1));
Csq = randn(size(A, 1), size(A, 1));
diagmm_ = @() diagmm(Ad, Bsq, Csq);

Atr = tril(Asy);
trmm_implicit_ = @() trmm_implicit(Atr, Bsq);

Asq = randn(size(A, 1), size(A, 1));
gemm_prop_ = @() gemm_implicit_noup(Asq, Bsq, Csq);

b.benchmark('gemm_implicit', reps, gemm_implicit_);
b.benchmark('gemm_implicit_noup', reps, gemm_implicit_noup_);
b.benchmark('gemm_implicit_compact', reps, gemm_implicit_compact_);
b.benchmark('gemm_implicit_coeff', reps, gemm_implicit_coeff_);
b.benchmark('gemm_implicit_double_coeff', reps, gemm_implicit_double_coeff_);

b.benchmark('gemm_prop', reps, gemm_prop_);
b.benchmark('trmm_implicit', reps, trmm_implicit_);
b.benchmark('diagmm', reps, diagmm_);
end

function [C, time] = diagmm(A, B, C)
tic;
C = A * B;
time = toc;
end

function [B, time] = trmm_implicit(A, B)
tic;
B = A * B;
time = toc;
end

function [C, time] = gemm_implicit(A, B, C)
tic;
C = A * B + C;
time = toc;
end

function [C, time] = gemm_implicit_compact(A, B, C)
tic;
C += A * B;
time = toc;
end

function [C, time] = gemm_implicit_coeff(A, B, C)
tic;
C = 3.0 * A * B + C;
time = toc;
end

function [C, time] = gemm_implicit_double_coeff(A, B, C)
tic;
C = 3.0 * A * B + 3.0 * C;
time = toc;
end

function [C, time] = gemm_implicit_noup(A, B, C)
tic;
C = A * B;
time = toc;
end
