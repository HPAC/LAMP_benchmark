#ifndef EIGEN_MATRIX_CHAIN_H
#define EIGEN_MATRIX_CHAIN_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_matrix_chain(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_MATRIX_CHAIN_H
