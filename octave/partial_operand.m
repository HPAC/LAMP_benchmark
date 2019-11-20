function partial_operand(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

part_op_col_mult_nai_ = @() part_op_col_mult_nai(A, B);
part_op_col_add_nai_ = @() part_op_col_add_nai(A, B);
part_op_col_add_rec_ = @() part_op_col_add_rec(A, B);

part_op_ele_mult_nai_ = @() part_op_ele_mult_nai(A, B);
part_op_ele_add_nai_ = @() part_op_ele_add_nai(A, B);
part_op_ele_add_rec_ = @() part_op_ele_add_rec(A, B);

b.benchmark('part_op_col_mult_nai', reps, part_op_col_mult_nai_);
b.benchmark('part_op_col_add_nai', reps, part_op_col_add_nai_);
b.benchmark('part_op_col_add_rec', reps, part_op_col_add_rec_);

b.benchmark('part_op_ele_mult_nai', reps, part_op_ele_mult_nai_);
b.benchmark('part_op_ele_add_nai', reps, part_op_ele_add_nai_);
b.benchmark('part_op_ele_add_rec', reps, part_op_ele_add_rec_);
end

function [C, time] = part_op_ele_mult_nai(A, B)
tic;
C = (A * B)(2, 2);
time = toc;
end

function [C, time] = part_op_ele_add_nai(A, B)
tic;
C = (A + B)(2, 2);
time = toc;
end

function [C, time] = part_op_ele_add_rec(A, B)
tic;
C = A(2, 2) + B(2, 2);
time = toc;
end

function [C, time] = part_op_col_mult_nai(A, B)
tic;
C = (A * B)(:, 2);
time = toc;
end

function [C, time] = part_op_col_add_nai(A, B)
tic;
C = (A + B)(:, 2);
time = toc;
end

function [C, time] = part_op_col_add_rec(A, B)
tic;
C = A(:, 2) + B(:, 2);
time = toc;
end
