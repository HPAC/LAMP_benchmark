#include "../include/benchmarks.h"

using namespace arma;

void transposition_nn(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void transposition_tn(const mat& A, const mat& B, mat& C)
{
  C = trans(A) * B;
}

void transposition_nt(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B);
}

void transposition_tt(const mat& A, const mat& B, mat& C)
{
  C = trans(A) * trans(B);
}

void bench_transposition(Benchmarker &b, int n)
{
  auto m = n / 10;
  dmat A = randn<dmat>(m, m);
  dmat B = randn<dmat>(m, m);
  dmat C = randn<dmat>(m, m);
  b.benchmark("tr_nn_implicit", transposition_nn, A, B, C);
  b.benchmark("tr_tn_implicit", transposition_tn, A, B, C);
  b.benchmark("tr_nt_implicit", transposition_nt, A, B, C);
  b.benchmark("tr_tt_implicit", transposition_tt, A, B, C);
}
