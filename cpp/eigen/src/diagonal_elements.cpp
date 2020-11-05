#include "../include/benchmarks.h"

using namespace Eigen;

void diag_naive_mult(const MatrixXd &A, const MatrixXd &B, MatrixXd &C)
{
  C = (A * B).diagonal();
}

void diag_naive(const MatrixXd &A, const MatrixXd &B, MatrixXd &C)
{
  C = (A + B).diagonal();
}

void diag_recommended(const MatrixXd &A, const MatrixXd &B, MatrixXd &C)
{
  C = A.diagonal() + B.diagonal();
}

void bench_diagonal_elements(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Zero(n, 1);

  b.benchmark("diag_add_nai", diag_naive, A, B, C);
  b.benchmark("diag_add_rec", diag_recommended, A, B, C);
  b.benchmark("diag_mult_nai", diag_naive_mult, A, B, C);

//  MatrixXd test1 = C;
//  diag_naive_mult(A, B, test1);
//  std::chrono::high_resolution_clock::time_point t1, t2;
//  t1 = std::chrono::high_resolution_clock::now();
//  MatrixXd test2 = A * B;
//  t2 = std::chrono::high_resolution_clock::now();
//  auto time_verification = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;
//  std::cout << "Diagonal mult equal: " << test1.isApprox(test2.diagonal(), 1e-11) <<  "Time for multiplication: " << time_verification << std::endl;
//  std::cout << "==========" << std::endl;
//  std::cout << test1 << std::endl;
//  std::cout << "----------" << std::endl;
//  std::cout << test2.diagonal() << std::endl;
//  std::cout << "@@@@@@@@@@"<< std::endl;
}
