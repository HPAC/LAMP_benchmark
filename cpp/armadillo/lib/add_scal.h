#ifndef ARMADILLO_ADD_SCAL_H
#define ARMADILLO_ADD_SCAL_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_add_scal(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_ADD_SCAL_H
