#ifndef ARMADILLO_GEMM_H
#define ARMADILLO_GEMM_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_gemm(const mat& A, const mat& B, const mat& C, Benchmarker& b);

#endif //ARMADILLO_GEMM_H
