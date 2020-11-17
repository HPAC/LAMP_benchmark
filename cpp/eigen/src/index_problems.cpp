#include "../include/benchmarks.h"

using namespace Eigen;

void loop_naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd temp = MatrixXd::Zero(A.rows(), B.cols());
  for (uint32_t i = 0; i < C.rows(); i++) {
    temp = A * B;
    C(i, 0) = temp(i, i);
  }
}

void loop_recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd temp = A * B;
  for (uint32_t i = 0; i < C.rows(); i++) {
    C(i, 0) = temp(i, i);
  }
}

void bench_index_problems(Benchmarker& b, int n)
{
  auto m = n / 10;
  MatrixXd A = MatrixXd::Random(m, m);
  MatrixXd B = MatrixXd::Random(m, m);
  MatrixXd C = MatrixXd::Random(m, 1);

  b.benchmark("loop_nai", loop_naive, A, B, C);
  b.benchmark("loop_rec", loop_recommended, A, B, C);
}
