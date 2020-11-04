#include "../include/benchmarks.h"

using namespace arma;

void diag_naive_mult(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A * B);
}

void diag_naive(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A + B);
}

void diag_recommended(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A) + diagvec(B);
}

void bench_diagonal_elements(Benchmarker& b, int n)
{
  dmat A = randn<dmat>(n, n);
  dmat B = randn<dmat>(n, n);
  dmat C = zeros<dmat>(A.n_rows, 1);

  b.benchmark("diag_add_nai", diag_naive, A, B, C);
  b.benchmark("diag_add_rec", diag_recommended, A, B, C);
  b.benchmark("diag_mult_nai", diag_naive_mult, A, B, C);
}
