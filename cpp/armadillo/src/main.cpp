#include <iostream>

#include "../include/benchmarks.h"

int main(int argc, char* argv[])
{
  const int n = std::atoi(std::getenv("LAMP_N"));
  const int cache_size = std::atoi(std::getenv("LAMP_L3_CACHE_SIZE"));
  const int threads = std::atoi(std::getenv("OMP_NUM_THREADS"));
  const int reps = std::atoi(std::getenv("LAMP_REPS"));

  const string output_dir = string(std::getenv("LAMP_OUTPUT_DIR"));
  string file_name = output_dir + "armadillo_" + std::to_string(threads) + ".txt";
  string file_timings_name = output_dir + "armadillo_" + std::to_string(threads) + "_timings.txt";
  string name = "Armadillo";

  Benchmarker b(name, file_name, file_timings_name, cache_size, reps, ';');

  // bench_gemm(b, n);
  // bench_syrk(b, n);
  // bench_syr2k(b, n);
  // bench_add_scal(b, n);

  // bench_matrix_chain(b, n);
  // bench_subexpression(b, n);
  // bench_partial_operand(b, n);
  // bench_loop_translation(b, n);
  // bench_diagonal_elements(b, n);
  // bench_properties_solve(b, n);
  // bench_composed_operations(b, n);
  // bench_transposition(b, n);
  // bench_index_problems(b, n);
  // bench_partitioned_matrices(b, n);
  bench_properties_solve_sparse(b, 100000, 0.00001);

  return 0;
}
