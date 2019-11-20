#ifndef EIGEN_SYR2K_H
#define EIGEN_SYR2K_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_syr2k(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b);

#endif //EIGEN_SYR2K_H
