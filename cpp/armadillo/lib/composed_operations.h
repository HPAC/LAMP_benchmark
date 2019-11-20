#ifndef ARMADILLO_COMPOSED_OPERATIONS_H
#define ARMADILLO_COMPOSED_OPERATIONS_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_composed_operations(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_COMPOSED_OPERATIONS_H
