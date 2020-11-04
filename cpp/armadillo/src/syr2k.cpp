#include "../include/benchmarks.h"

using namespace arma;

void syr2k_implicit(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B) + B * trans(A) + C;
}

void syr2k_implicit_compact(const mat& A, const mat& B, mat& C)
{
  C += A * trans(B) + B * trans(A);
}

void syr2k_implicit_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * trans(B) + B * trans(A) + C;
}

void syr2k_implicit_double_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * trans(B) + B * trans(A) + 3.0 * C;
}

void syr2k_implicit_noup(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B) + B * trans(A);
}

void bench_syr2k(Benchmarker &b, int n)
{
  auto k = n;
  dmat A = randn<dmat>(n, k);
  dmat B = randn<dmat>(n, k);
  dmat C = randn<dmat>(n, n);
  C = C * trans(C);

  b.benchmark("syr2k_implicit", syr2k_implicit, A, B, C);
  b.benchmark("syr2k_implicit_compact", syr2k_implicit_compact, A, B, C);
  b.benchmark("syr2k_implicit_noup", syr2k_implicit_noup, A, B, C);
  b.benchmark("syr2k_implicit_coeff", syr2k_implicit_coeff, A, B, C);
  b.benchmark("syr2k_implicit_double_coeff", syr2k_implicit_double_coeff, A, B, C);
}
