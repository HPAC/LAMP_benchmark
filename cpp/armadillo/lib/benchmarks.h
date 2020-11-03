#ifndef LAMP_BENCHMARK_BENCHMARKS_H
#define LAMP_BENCHMARK_BENCHMARKS_H

#include "../../benchmarker/benchmarker.h"

void bench_add_scal(int n, Benchmarker& b);
void bench_properties_solve(int m, int rhs, Benchmarker& b);
void bench_syrk(int n, int k, Benchmarker& b);
void bench_gemm(int m, int k, int n, Benchmarker& b);

#endif //LAMP_BENCHMARK_BENCHMARKS_H
