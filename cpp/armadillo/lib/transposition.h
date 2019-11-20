#ifndef ARMADILLO_TRANSPOSITION_H
#define ARMADILLO_TRANSPOSITION_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_transposition(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_TRANSPOSITION_H
