#ifndef EIGEN_ADD_SCAL_H
#define EIGEN_ADD_SCAL_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_add_scal(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_ADD_SCAL_H
