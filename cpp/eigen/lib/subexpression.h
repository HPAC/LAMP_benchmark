#ifndef EIGEN_SUBEXPRESSION_H
#define EIGEN_SUBEXPRESSION_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_subexpression(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_SUBEXPRESSION_H
