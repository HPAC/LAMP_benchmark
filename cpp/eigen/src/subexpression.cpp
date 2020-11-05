#include "../include/benchmarks.h"

using namespace Eigen;

void subexpression_naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B + A * B;
}

void subexpression_recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
  C = C + C;
}

void bench_subexpression(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Zero(n, n);

  b.benchmark("subexpr_nai", subexpression_naive, A, B, C);
  b.benchmark("subexpr_rec", subexpression_recommended, A, B, C);
}
