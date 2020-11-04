#ifndef LAMP_BENCHMARK_BENCHMARKS_H
#define LAMP_BENCHMARK_BENCHMARKS_H

#include "../../benchmarker/benchmarker.h"
#include "armadillo"

void bench_add_scal(Benchmarker& b, int n);
void bench_properties_solve(Benchmarker &b, int n);
void bench_composed_operations(Benchmarker &b, int n);
void bench_syrk(Benchmarker &b, int n);
void bench_gemm(Benchmarker &b, int n);
void bench_syr2k(Benchmarker &b, int n);
void bench_transposition(Benchmarker &b, int n);
void bench_subexpression(Benchmarker& b, int n);
void bench_matrix_chain(Benchmarker& b, int n);
void bench_diagonal_elements(Benchmarker& b, int n);
void bench_partial_operand(Benchmarker& b, int n);
void bench_index_problems(Benchmarker& b, int n);
void bench_loop_translation(Benchmarker& b, int n);
void bench_partitioned_matrices(Benchmarker& b, int n);

#endif //LAMP_BENCHMARK_BENCHMARKS_H
