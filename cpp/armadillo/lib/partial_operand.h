#ifndef ARMADILLO_PARTIAL_OPERAND_H
#define ARMADILLO_PARTIAL_OPERAND_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_partial_operand(const mat& A, const mat& B, Benchmarker& b);

#endif //ARMADILLO_PARTIAL_OPERAND_H
