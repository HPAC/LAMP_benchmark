#ifndef ARMADILLO_PROPERTIES_SOLVE_H
#define ARMADILLO_PROPERTIES_SOLVE_H

#include "tools.h"
#include <armadillo>
#include "../../benchmarker/benchmarker.h"

using namespace arma;

void bench_properties_solve(int m, int rhs, Benchmarker& b);

#endif //ARMADILLO_PROPERTIES_SOLVE_H
