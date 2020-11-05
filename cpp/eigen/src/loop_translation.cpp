#include "../include/benchmarks.h"

using namespace Eigen;

void loop_translation_naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  for (uint32_t i = 0; i < C.cols(); i++) {
    C.col(i) = A * B.col(i);
  }
}

void loop_translation_recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
}

void bench_loop_translation(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Random(n, n);

  b.benchmark("loop_translation_nai", loop_translation_naive, A, B, C);
  b.benchmark("loop_translation_rec", loop_translation_recommended, A, B, C);
}
