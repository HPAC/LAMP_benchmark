% A (m,m) B (m,m) C (m,m,n)
function index_problems(A, B, C, b)

reps = str2num(getenv('LAMP_REPS'));

naive_loop_= @() naive_loop(A, B, C);
recommended_loop_= @() recommended_loop(A, B, C);

isequal(naive_loop_, recommended_loop_)

b.benchmark('loop_translation_nai', reps, naive_loop_);
b.benchmark('loop_translation_rec', reps, recommended_loop_);
end

function [C, time] = naive_loop(A, B, C)
tic;
for i = 1:size(C, 2)
  C(:, i) = A * B(:, i);
end
time = toc;
end

function [C, time] = recommended_loop(A, B, C)
tic;
C = A * B;
time = toc;
end
