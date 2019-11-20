#ifndef ARMADILLO_DIAGONAL_ELEMENTS_H
#define ARMADILLO_DIAGONAL_ELEMENTS_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_diagonal_elements(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_DIAGONAL_ELEMENTS_H
