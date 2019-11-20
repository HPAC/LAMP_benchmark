#ifndef ARMADILLO_MATRIX_CHAIN_H
#define ARMADILLO_MATRIX_CHAIN_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_matrix_chain(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_MATRIX_CHAIN_H
