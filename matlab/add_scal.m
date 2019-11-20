function add_scal(A, B, b)

reps = str2num(getenv('LAMP_REPS'));

add_ = @() add(A, B);
scal_ = @() scal(A);

b.benchmark('add', reps, add_);
b.benchmark('scal', reps, scal_);
end

function [res, time] = add(A, B)
at = A;
bt = B;
tic;
bt = at + bt;
time = toc;
res = bt;
end

function [res, time] = scal(A)
at = A;
tic;
at = 3.0 * at;
time = toc;
res = at;
end
