#include "../include/benchmarks.h"

using namespace arma;

void l_r_orig(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = m * A * B;
}

void l_r_guid(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = (m * A) * B;
}

void r_l_orig(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = A * B * m;
}

void r_l_guid(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = A * (B * m);
}

void mixed_orig(const mat& A, const mat& B, const mat& m1, const mat& m2, mat& C)
{
  C = A * m1 * m2 * B;
}

void mixed_guid(const mat& A, const mat& B, const mat& m1, const mat& m2, mat& C)
{
  C = (A * m1) * (m2 * B);
}

void bench_matrix_chain(Benchmarker& b, int n)
{
  dmat A = randn<mat>(n, n);
  dmat B = randn<mat>(n, n);

  dmat M1 = randn<dmat>(n / 5, n);
  dmat C = zeros<dmat>(n / 5, n);
  b.benchmark("mc_l_r_orig", l_r_orig, A, B, M1, C);
  b.benchmark("mc_l_r_guid", l_r_guid, A, B, M1, C);

  dmat M2 = randn<dmat>(n, n / 5);
  C = zeros<dmat>(n, n / 5);
  b.benchmark("mc_r_l_orig", r_l_orig, A, B, M2, C);
  b.benchmark("mc_r_l_guid", r_l_guid, A, B, M2, C);

  // Mixed
  C = zeros<dmat>(n, n);
  M1 = randn<dmat>(n, n / 5);
  M2 = randn<dmat>(n / 5, n);
  b.benchmark("mc_mixed_orig", mixed_orig, A, B, M1, M2, C);
  b.benchmark("mc_mixed_guid", mixed_guid, A, B, M1, M2, C);
}
