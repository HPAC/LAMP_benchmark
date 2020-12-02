#include "../include/benchmarks.h"

using namespace Eigen;

void my_solve(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.partialPivLu().solve(B);
}

void bench_properties_solve(Benchmarker& b, int n)
{
  MatrixXd C = MatrixXd::Random(n, 10);
  MatrixXd B = MatrixXd::Random(n, 10);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //naive(A, B, c1);
  //recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << c1.isApprox(c2) << std::endl;

  // SPD
  MatrixXd A = MatrixXd::Random(n, n);
  A = A.selfadjointView<Eigen::Lower>();
  A += MatrixXd::Identity(n, n) * n;
  std::cout << "A symmetric: " << A.isApprox(A.transpose()) << std::endl;
  Eigen::LLT<Eigen::MatrixXd> lltOfAspd(A); // compute the Cholesky decomposition of A
  if (lltOfAspd.info() == Eigen::NumericalIssue)
    std::cout << "A SPD: False" << std::endl;
  else
    std::cout << "A SPD: True" << std::endl;
  b.benchmark("solve_spd", my_solve, A, B, C);

  // Symmetric
  A.resize(n, n);
  A.setRandom();
  A = A.selfadjointView<Eigen::Lower>();
  A(0, 0) = -1.0;
  std::cout << "A symmetric: " << A.isApprox(A.transpose()) << std::endl;
  Eigen::LLT<Eigen::MatrixXd> lltOfAsym(A); // compute the Cholesky decomposition of A
  if (lltOfAsym.info() == Eigen::NumericalIssue)
    std::cout << "A SPD: False" << std::endl;
  else
    std::cout << "A SPD: True" << std::endl;
  b.benchmark("solve_sym", my_solve, A, B, C);

  // Triangular
  A.resize(n, n);
  A.setRandom();
  A = A.triangularView<Eigen::Lower>(); // This step creates a full matrix from the view.
  //std::cout << "A triangular: " << A.isApprox(A.triangularView<Eigen::Lower>()) << std::endl;
  b.benchmark("solve_tri", my_solve, A, B, C);

  // Diagonal
  A.resize(n, n);
  A.setRandom();
  A = A.diagonal().asDiagonal();
  //std::cout << "A diagonal: " << A.isApprox(A.diagonal().asDiagonal()) << std::endl;
  b.benchmark("solve_dia", my_solve, A, B, C);
}
