#ifndef ARMADILLO_INDEX_PROBLEMS_H
#define ARMADILLO_INDEX_PROBLEMS_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_index_problems(const mat& A, const mat& B, const mat& C, Benchmarker& b);

#endif //ARMADILLO_INDEX_PROBLEMS_H
