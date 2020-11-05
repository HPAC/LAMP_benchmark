#include "../include/benchmarks.h"

using namespace Eigen;

void transposition_nn(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
}

void transposition_tn(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.transpose() * B;
}

void transposition_nt(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B.transpose();
}

void transposition_tt(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.transpose() * B.transpose();
}

void bench_transposition(Benchmarker &b, int n)
{
  auto m = n / 10;
  MatrixXd A = MatrixXd::Random(m, m);
  MatrixXd B = MatrixXd::Random(m, m);
  MatrixXd C = MatrixXd::Zero(m, m);

  b.benchmark("tr_nn_implicit", transposition_nn, A, B, C);
  b.benchmark("tr_tn_implicit", transposition_tn, A, B, C);
  b.benchmark("tr_nt_implicit", transposition_nt, A, B, C);
  b.benchmark("tr_tt_implicit", transposition_tt, A, B, C);
}
