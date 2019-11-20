#ifndef EIGEN_GEMM_H
#define EIGEN_GEMM_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_gemm(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b);

#endif //EIGEN_GEMM_H
