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
#include <armadillo>

using namespace arma;

int main(int argc, char* argv[])
{

  std::cout << "lala";
  int m = 3000;
  int k = 550;
  int n = 3000;

  int tn = 80;
  int ipn = 80;
  int l = 100;
  int p = 1500;

  dmat A, B, C, A1, A2;

  const char* lamp_output_dir = std::getenv("LAMP_OUTPUT_DIR");
  const char* threads = std::getenv("OMP_NUM_THREADS");
  string file_name = string(lamp_output_dir) + "armadillo_" + string(threads) + "1.txt";
  string file_timings_name = string(lamp_output_dir) + "armadillo_" + string(threads) + "_timings1.txt";
  string name = "Armadillo";

  Benchmarker b(name, file_name, file_timings_name, 10, ';');

  bench_add_scal(n, b);

  // Properties Solve
  bench_properties_solve(m, l, b);

  // SYRK
  bench_syrk(n, k, b);

  // GEMM
  A = randn<mat>(m, k);
  B = randn<mat>(k, n);
  C = randn<mat>(m, n);

  bench_gemm(A, B, C, b);

  // SYR2K

  A = randn<mat>(n, k);
  B = randn<mat>(n, k);
  C = randn<mat>(n, n);
  C = C * trans(C);

  bench_syr2k(A, B, C, b);

  // Transposition

  A = randn<mat>(tn, tn);
  B = randn<mat>(tn, tn);

  bench_transposition(A, B, b);

  // Common Subexpression

  A = randn<mat>(m, k);
  B = randn<mat>(k, n);

  bench_subexpression(A, B, b);

  // Composed Operations

  A = randn<mat>(n, n);
  B = randn<mat>(n, l);

  bench_composed_operations(A, B, b);

  // Matrix Chain Problem

  A = randn<mat>(m, k);
  B = randn<mat>(k, n);

  bench_matrix_chain(A, B, b);

  // Diagonal elements

  A = randn<mat>(n, n);
  B = randn<mat>(n, n);

  bench_diagonal_elements(A, B, b);

  // Diagonal elements

  A = randn<mat>(n, n);
  B = randn<mat>(n, n);

  bench_partial_operand(A, B, b);

  // Index problems

  A = randn<mat>(ipn, ipn);
  B = randn<mat>(ipn, ipn);
  C = randn<mat>(ipn, 1);

  bench_index_problems(A, B, C, b);

  // Loop translation
  A = randn<mat>(n, n);
  B = randn<mat>(n, n);
  C = randn<mat>(n, n);

  bench_loop_translation(A, B, C, b);

  // Partitioned Matrices

  A1 = randn<mat>(p, p);
  A2 = randn<mat>(p, p);
  B = randn<mat>(2 * p, 2 * p);

  bench_partitioned_matrices(A1, A2, B, b);

  return 0;
}
