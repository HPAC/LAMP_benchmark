function matrix_chain(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

n = size(A, 2);

C1 = randn(n/5, n);
C2 = randn(n, n/5);
l_r_orig_ = @() l_r_orig(A, B, C1);
l_r_guid_ = @() l_r_guid(A, B, C1);
r_l_orig_ = @() r_l_orig(A, B, C2);
r_l_guid_ = @() r_l_guid(A, B, C2);

C11 = randn(n, n/5);
C21 = randn(n/5, n);
mixed_orig_ = @() mixed_orig(A, B, C11, C21);
mixed_guid_ = @() mixed_guid(A, B, C11, C21);

b.benchmark('mc_l_r_orig', reps, l_r_orig_);
b.benchmark('mc_l_r_guid', reps, l_r_guid_);
b.benchmark('mc_r_l_orig', reps, r_l_orig_);
b.benchmark('mc_r_l_guid', reps, r_l_guid_);
b.benchmark('mc_mixed_orig', reps, mixed_orig_);
b.benchmark('mc_mixed_guid', reps, mixed_guid_);
end

function [C, time] = l_r_orig(A, B, m)
C = zeros(size(m, 1), size(B, 2));
tic;
C = m * A * B;
time = toc;
end

function [C, time] = l_r_guid(A, B, m)
C = zeros(size(m, 1), size(B, 2));
tic;
C = (m * A) * B;
time = toc;
end

function [C, time] = r_l_orig(A, B, m)
C = zeros(size(A, 1), size(m, 2));
tic;
C = A * B * m;
time = toc;
end

function [C, time] = r_l_guid(A, B, m)
C = zeros(size(A, 1), size(m, 2));
tic;
C = A * (B * m);
time = toc;
end

function [C, time] = mixed_orig(A, B, m1, m2)
C = zeros(size(A, 1), size(B, 2));
tic;
C = A * m1 * m2 * B;
time = toc;
end

function [C, time] = mixed_guid(A, B, m1, m2)
C = zeros(size(A, 1), size(B, 2));
tic;
C = (A * m1) * (m2 * B);
time = toc;
end
