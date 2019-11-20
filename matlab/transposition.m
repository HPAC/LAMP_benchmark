function transposition(A ,B, C, b)

reps = str2num(getenv('LAMP_REPS'));

transposition_nn_ = @() transposition_nn(A, B, C);
transposition_tn_ = @() transposition_tn(A, B, C);
transposition_nt_ = @() transposition_nt(A, B, C);
transposition_tt_ = @() transposition_tt(A, B, C);

b.benchmark('tr_nn_implicit', reps, transposition_nn_);
b.benchmark('tr_tn_implicit', reps, transposition_tn_);
b.benchmark('tr_nt_implicit', reps, transposition_nt_);
b.benchmark('tr_tt_implicit', reps, transposition_tt_);
end


function [C, time] = transposition_nn(A, B, C)
tic;
C = A * B;
time = toc;
end

function [C, time] = transposition_tn(A, B, C)
tic;
C = A' * B;
time = toc;
end

function [C, time] = transposition_nt(A, B, C)
tic;
C = A * B';
time = toc;
end

function [C, time] = transposition_tt(A, B, C)
tic;
C = A' * B';
time = toc;
end
