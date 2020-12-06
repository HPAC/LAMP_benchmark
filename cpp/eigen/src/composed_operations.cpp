#include "../include/benchmarks.h"

using namespace Eigen;

void solve_naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.inverse() * B;
}

void solve_recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.partialPivLu().solve(B);
}

void bench_composed_operations(Benchmarker &b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, 200);
  MatrixXd C = MatrixXd::Zero(n, 200);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //solve_naive(A, B, c1);
  //solve_recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << c1.isApprox(c2) << std::endl;

  b.benchmark("solve_nai", solve_naive, A, B, C);
  b.benchmark("solve_rec", solve_recommended, A, B, C);

  //B.setRandom(n , n / 2);
  //C.setZero(n, n / 2);
  //b.benchmark("solve_large_nai", solve_naive, A, B, C);
  //b.benchmark("solve_large_rec", solve_recommended, A, B, C);
}
