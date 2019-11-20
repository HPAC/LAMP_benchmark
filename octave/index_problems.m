% A (m,m) B (m,m) C (m,m,n)
function index_problems(A, B, C, b)

reps = str2num(getenv('LAMP_REPS'));

naive_loop_invariant_ = @() naive_loop_invariant(A, B, C);
recommended_loop_invariant_ = @() recommended_loop_invariant(A, B, C);

b.benchmark('loop_nai', reps, naive_loop_invariant_);
b.benchmark('loop_rec', reps, recommended_loop_invariant_);
end

function [C, time] = naive_loop_invariant(A, B, C)
tic;
temp = zeros(size(A, 1), size(B, 2));
for i = 1:size(C, 1)
        temp = A*B;
        C(i) = temp(i, i);
    end
    time = toc;
end

function [C, time] = recommended_loop_invariant(A, B, C)
tic;
temp = A*B;
for i = 1:size(C, 1)
        C(i) = temp(i, i);
    end
    time = toc;
end
