#include "../include/benchmarks.h"

using namespace Eigen;

void naive_col_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A + B).col(2);
}

void recommended_col_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.col(2) + B.col(2);
}

void naive_col_mult(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A * B).col(2);
}

void naive_ele_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = (A + B)(1, 1);
}

void recommended_ele_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = A(1, 1) + B(1, 1);
}

void naive_ele_mult(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = (A * B)(1, 1);
}

void bench_partial_operand(Benchmarker& b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Zero(n, 1);
  b.benchmark("part_op_col_add_nai", naive_col_add, A, B, C);
  b.benchmark("part_op_col_add_rec", recommended_col_add, A, B, C);
  b.benchmark("part_op_col_mult_nai", naive_col_mult, A, B, C);

  C.setZero(1, 1);
  b.benchmark("part_op_ele_add_nai", naive_ele_add, A, B, C);
  b.benchmark("part_op_ele_add_rec", recommended_ele_add, A, B, C);
  b.benchmark("part_op_ele_mult_nai", naive_ele_mult, A, B, C);
}
