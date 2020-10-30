#include <iostream>

#include "add_scal.h"
#include "composed_operations.h"
#include "diagonal_elements.h"
#include "gemm.h"
#include "index_problems.h"
#include "loop_translation.h"
#include "matrix_chain.h"
#include "partial_operand.h"
#include "partitioned_matrices.h"
#include "properties_solve.h"
#include "subexpression.h"
#include "syr2k.h"
#include "syrk.h"
#include "transposition.h"
#include <Eigen/Dense>

using namespace Eigen;

int main(int argc, char* argv[])
{

  int m = 3000;
  int k = 550;
  int n = 3000;

  int tn = 80;
  int ipn = 80;
  int l = 100;
  int p = 1500;

  MatrixXd A, B, C, A1, A2;

  Benchmarker b("eigen");

  auto n_threads = Eigen::nbThreads();
  std::cout << "Eigen threads: " << n_threads << std::endl;

  A = MatrixXd::Random(n, n);
  B = MatrixXd::Random(n, n);
  bench_add_scal(A, B, b);

  // Properties Solve

  bench_properties_solve(m, l, b);

  // SYRK

  A = MatrixXd::Random(n, k);
  C = MatrixXd::Random(n, n);
  C = C * C.transpose();

  bench_syrk(A, C, b);

  // GEMM

  A = MatrixXd::Random(m, k);
  B = MatrixXd::Random(k, n);
  C = MatrixXd::Random(m, n);

  bench_gemm(A, B, C, b);

  // SYR2K

  A = MatrixXd::Random(n, k);
  B = MatrixXd::Random(n, k);
  C = MatrixXd::Random(n, n);
  C = C * C.transpose();

  bench_syr2k(A, B, C, b);

  // Transposition

  A = MatrixXd::Random(tn, tn);
  B = MatrixXd::Random(tn, tn);

  bench_transposition(A, B, b);

  // Common Subexpression

  A = MatrixXd::Random(m, k);
  B = MatrixXd::Random(k, n);

  bench_subexpression(A, B, b);

  // Composed Operations

  A = MatrixXd::Random(n, n);
  B = MatrixXd::Random(n, l);

  bench_composed_operations(A, B, b);

  // Matrix Chain Problem

  A = MatrixXd::Random(m, k);
  B = MatrixXd::Random(k, n);

  bench_matrix_chain(A, B, b);

  // Diagonal elements

  A = MatrixXd::Random(n, n);
  B = MatrixXd::Random(n, n);

  bench_diagonal_elements(A, B, b);

  // Diagonal elements

  A = MatrixXd::Random(n, n);
  B = MatrixXd::Random(n, n);

  bench_partial_operand(A, B, b);

  // Index problems

  A = MatrixXd::Random(ipn, ipn);
  B = MatrixXd::Random(ipn, ipn);
  C = MatrixXd::Random(ipn, 1);

  bench_index_problems(A, B, C, b);

  // Index problems

  A = MatrixXd::Random(n, n);
  B = MatrixXd::Random(n, n);
  C = MatrixXd::Random(n, n);

  bench_loop_translation(A, B, C, b);

  // Partitioned Matrices

  A1 = MatrixXd::Random(p, p);
  A2 = MatrixXd::Random(p, p);
  B = MatrixXd::Random(2 * p, 2 * p);

  bench_partitioned_matrices(A1, A2, B, b);

  return 0;
}
