#ifndef ARMADILLO_SYR2K_H
#define ARMADILLO_SYR2K_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_syr2k(const mat& A, const mat& B, const mat& C, Benchmarker& b);

#endif //ARMADILLO_SYR2K_H
