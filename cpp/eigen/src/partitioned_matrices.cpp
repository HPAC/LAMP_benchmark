#include "../include/benchmarks.h"

using namespace Eigen;

void implicit_partitioned(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd tempA = MatrixXd::Zero(B.rows(), B.cols());
  tempA.block(0, 0, A1.rows(), A1.cols()) = A1;
  tempA.block(A1.rows(), A2.cols(), A2.rows(), A2.cols()) = A2;
  C = tempA.partialPivLu().solve(B);
}

void explicit_partitioned(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, MatrixXd& C)
{
  C.block(0, 0, A1.rows(), B.cols()) = A1.partialPivLu().solve(B.block(0, 0, A1.rows(), B.cols()));
  C.block(A1.rows(), 0, A2.rows(), B.cols()) = A2.partialPivLu().solve(B.block(A1.rows(), 0, A2.rows(), B.cols()));
}

void bench_partitioned_matrices(Benchmarker& b, int n)
{
  auto m = n / 10;
  MatrixXd A1 = MatrixXd::Random(m, m);
  MatrixXd A2 = MatrixXd::Random(m, m);
  MatrixXd B = MatrixXd::Random(2 * m, 2 * m);
  MatrixXd C = MatrixXd::Zero(2 * m, 2 * m);

  b.benchmark("compact", implicit_partitioned, A1, A2, B, C);
  b.benchmark("blocked", explicit_partitioned, A1, A2, B, C);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //implicit_partitioned(A1, A2, B, c1);
  //explicit_partitioned(A1, A2, B, c2);
  //std::cout << "Partitioned Matrices equal: " << c1.isApprox(c2, 1e-11) << std::endl;
  //std::cout << "Partitioned Matrices equal: " << (c1 - c2).norm() / c1.norm() << std::endl;
}
