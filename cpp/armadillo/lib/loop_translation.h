#ifndef ARMADILLO_LOOP_TRANSLATION_H
#define ARMADILLO_LOOP_TRANSLATION_H

#include "tools.h"
#include <armadillo>

using namespace arma;

void bench_loop_translation(const mat& A, const mat& B, const mat& C, Benchmarker& b);

#endif //ARMADILLO_LOOP_TRANSLATION_H
