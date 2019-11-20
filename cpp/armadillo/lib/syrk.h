#ifndef ARMADILLO_SYRK_H
#define ARMADILLO_SYRK_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_syrk(const mat& A, const mat& C, Benchmarker& b);

#endif //ARMADILLO_SYRK_H
