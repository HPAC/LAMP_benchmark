#ifndef EIGEN_TRANSPOSITION_H
#define EIGEN_TRANSPOSITION_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_transposition(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_TRANSPOSITION_H
