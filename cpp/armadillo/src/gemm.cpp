#include "../include/benchmarks.h"

using namespace arma;

void gemm_implicit(const mat& A, const mat& B, mat& C)
{
  C = A * B + C;
}

void gemm_implicit_compact(const mat& A, const mat& B, mat& C)
{
  C += A * B;
}

void gemm_implicit_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * B + C;
}

void gemm_implicit_double_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * B + 3.0 * C;
}

void gemm_implicit_noup(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void trmm_implicit_compact(const mat& A, mat& B)
{
  B *= A;
}

void trmm_implicit(const mat& A, mat& B)
{
  B = A * B;
}

void diagmm(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void bench_gemm(Benchmarker &b, int n)
{
  dmat A = randn<dmat>(n, n);
  dmat B = randn<dmat>(n, n);
  dmat C = randn<dmat>(n, n);
  b.benchmark("gemm_implicit", gemm_implicit, A, B, C);
  b.benchmark("gemm_implicit_compact", gemm_implicit_compact, A, B, C);
  b.benchmark("gemm_implicit_noup", gemm_implicit_noup, A, B, C);
  b.benchmark("gemm_implicit_coeff", gemm_implicit_coeff, A, B, C);
  b.benchmark("gemm_implicit_double_coeff", gemm_implicit_double_coeff, A, B, C);

  A = trimatl(randn<dmat>(n, n));
  b.benchmark("trmm_implicit", trmm_implicit, A, B);
  b.benchmark("trmm_implicit_compact", trmm_implicit_compact, A, B);

  A = diagmat(randn<dmat>(n, n));
  b.benchmark("diagmm", diagmm, A, B, C);
}
