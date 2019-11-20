#ifndef EIGEN_INDEX_PROBLEMS_H
#define EIGEN_INDEX_PROBLEMS_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_index_problems(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b);

#endif //EIGEN_INDEX_PROBLEMS_H
