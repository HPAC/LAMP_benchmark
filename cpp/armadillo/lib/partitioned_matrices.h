#ifndef ARMADILLO_PARTITIONED_MATRICES_H
#define ARMADILLO_PARTITIONED_MATRICES_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_partitioned_matrices(const mat& A1, const mat& A2, const mat& B, Benchmarker& b);

#endif //ARMADILLO_PARTITIONED_MATRICES_H
