#ifndef EIGEN_COMPOSED_OPERATIONS_H
#define EIGEN_COMPOSED_OPERATIONS_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_composed_operations(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_COMPOSED_OPERATIONS_H
