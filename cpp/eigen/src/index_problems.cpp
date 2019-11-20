#include "../lib/index_problems.h"

static void naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd temp = MatrixXd::Zero(A.rows(), B.cols());
  for (uint32_t i = 0; i < C.rows(); i++) {
    temp = A * B;
    C(i, 0) = temp(i, i);
  }
}

static void recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd temp = A * B;
  for (uint32_t i = 0; i < C.rows(); i++) {
    C(i, 0) = temp(i, i);
  }
}

void bench_index_problems(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, naive(At, Bt, Ct), naive_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, recommended(At, Bt, Ct), recommended_v[i]);
  }

  b.add(naive_v, "loop_nai");
  b.add(recommended_v, "loop_rec");
}
