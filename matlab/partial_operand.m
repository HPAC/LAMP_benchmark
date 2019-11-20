function partial_operand(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

% implicit_ = @() implicit(A, B);
% explicit_ = @() explicit(A, B);

% b.benchmark('part_op_nai', reps, implicit_);
% b.benchmark('part_op_rec', reps, explicit_);
end

% function [C, time] = implicit(A, B)
% tic;
% %C = (A + B)(:, 2);
% C = A+B
% time = toc;
% end

function [C, time] = explicit(A, B)
tic;
C = A(:, 2) + B(:, 2);
time = toc;
end
