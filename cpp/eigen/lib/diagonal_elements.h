#ifndef EIGEN_DIAGONAL_ELEMENTS_H
#define EIGEN_DIAGONAL_ELEMENTS_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_diagonal_elements(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_DIAGONAL_ELEMENTS_H
