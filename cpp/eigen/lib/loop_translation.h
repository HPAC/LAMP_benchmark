#ifndef EIGEN_LOOP_TRANSLATION_H
#define EIGEN_LOOP_TRANSLATION_H

#include "tools.h"
#include <Eigen/Dense>

using namespace Eigen;

void bench_loop_translation(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b);

#endif //EIGEN_LOOP_TRANSLATION_H
