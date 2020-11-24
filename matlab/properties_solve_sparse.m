function properties_solve_sparse(n, rhs, density, b)

  reps = str2num(getenv('LAMP_REPS'));

  B = randn(n, rhs);

  % General
  A = sprandn(n,n,density) + speye(n,n);
  fprintf("Cond number: %.1f, nnz: %d\n", condest(A), nnz(A))
  custom_solve_ = @() custom_solve(A, B);
  b.benchmark('solve_sp_gen', reps, custom_solve_);

  % Symmetric
  A = sprandn(n,n,density/2);
  A = A + A' + 2.0 * speye(n,n);
  fprintf("Cond number: %.1f, nnz: %d\n", condest(A), nnz(A))
  custom_solve_ = @() custom_solve(A, B);
  b.benchmark('solve_sp_sym', reps, custom_solve_);

  % SPD
  A = sprandn(n,n,density/2);
  A = A + A' + speye(n,n) * n;
  fprintf("Cond number: %.1f, nnz: %d\n", condest(A), nnz(A))
  custom_solve_ = @() custom_solve(A, B);
  b.benchmark('solve_sp_spd', reps, custom_solve_);

  % Triangular
  A = sprandn(n,n,2*density);
  A = tril(A) + speye(n,n);
  fprintf("Cond number: %.1f, nnz: %d\n", condest(A), nnz(A))
  custom_solve_ = @() custom_solve(A, B);
  b.benchmark('solve_sp_tri', reps, custom_solve_);

end

function [C, time] = custom_solve(A, B)
  C = zeros(size(B));
  tic;
  C = A\B;
  time = toc;
end

