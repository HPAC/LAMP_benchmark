#include "../include/benchmarks.h"

using namespace Eigen;

void l_r_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = m * A * B;
}

void l_r_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = (m * A) * B;
}

void r_l_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = A * B * m;
}

void r_l_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = A * (B * m);
}

void mixed_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m1, const MatrixXd& m2, MatrixXd& C)
{
  C = A * m1 * m2 * B;
}
void mixed_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m1, const MatrixXd& m2, MatrixXd& C)
{
  C = (A * m1) * (m2 * B);
}

void bench_matrix_chain(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);

  MatrixXd M1 = MatrixXd::Random(n / 5, n);
  MatrixXd C = MatrixXd::Zero(n / 5, n);
  b.benchmark("mc_l_r_orig", l_r_orig, A, B, M1, C);
  b.benchmark("mc_l_r_guid", l_r_guid, A, B, M1, C);

  MatrixXd M2 = MatrixXd::Random(n, n / 5);
  C.setZero(n, n);
  b.benchmark("mc_r_l_orig", r_l_orig, A, B, M2, C);
  b.benchmark("mc_r_l_guid", r_l_guid, A, B, M2, C);

  // Mixed
  C.setZero(n, n);
  M1.setRandom(n, n / 5);
  M2.setRandom(n / 5, n);
  b.benchmark("mc_mixed_orig", mixed_orig, A, B, M1, M2, C);
  b.benchmark("mc_mixed_guid", mixed_guid, A, B, M1, M2, C);
}
