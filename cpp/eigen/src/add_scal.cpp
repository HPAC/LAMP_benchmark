#include "../include/benchmarks.h"

using namespace Eigen;

static void add(const MatrixXd& A, MatrixXd& B)
{
  B = A + B;
}

static void scal(MatrixXd& A)
{
  A = 3.0 * A;
}

void bench_add_scal(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);

  b.benchmark("add", add, A, B);
  b.benchmark("scal", scal, A);
}
