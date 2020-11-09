#include "../include/benchmarks.h"

using namespace arma;

//static void naive_col(const mat& A, const mat& B, mat& C)
//{
  ////C = (A + B).col(2);
//}

//static void recommended_col(const mat& A, const mat& B, mat& C)
//{
  //C = A.col(2) + B.col(2);
//}

//static void naive_ele(const mat& A, const mat& B, mat& C)
//{
  ////C = (A + B)(1, 1);
//}

//static void recommended_ele(const mat& A, const mat& B, mat& C)
//{
  //C = A(1, 1) + B(1, 1);
//}

void bench_partial_operand(Benchmarker& b, int n)
{
//  dmat A = randn<dmat>(n, n);
//  dmat B = randn<dmat>(n, n);
  // b.benchmark("part_op_col_add_nai", naive_col, A, B, C);
  // b.benchmark("part_op_col_add_rec", recommended_col, A, B, C);

//  dmat C = zeros<dmat>(1, 1);
  // b.benchmark("part_op_ele_add_nai", naive_ele, A, B, C);
  // b.benchmark("part_op_ele_add_rec", recommended_ele, A, B, C);
}
