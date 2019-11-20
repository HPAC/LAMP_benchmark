#ifndef EIGEN_PARTIAL_OPERAND_H
#define EIGEN_PARTIAL_OPERAND_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_partial_operand(const MatrixXd& A, const MatrixXd& B, Benchmarker& b);

#endif //EIGEN_PARTIAL_OPERAND_H
