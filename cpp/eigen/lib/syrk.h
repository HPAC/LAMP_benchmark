#ifndef EIGEN_SYRK_H
#define EIGEN_SYRK_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_syrk(const MatrixXd& A, const MatrixXd& C, Benchmarker& b);

#endif //EIGEN_SYRK_H
