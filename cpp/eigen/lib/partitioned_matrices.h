#ifndef EIGEN_PARTITIONED_MATRICES_H
#define EIGEN_PARTITIONED_MATRICES_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_partitioned_matrices(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_PARTITIONED_MATRICES_H
