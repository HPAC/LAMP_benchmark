#include "../lib/subexpression.h"

static void naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B + A * B;
}

static void recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
  C = C + C;
}

void bench_subexpression(const MatrixXd& A, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  MatrixXd C = MatrixXd::Zero(A.rows(), B.cols());
  MatrixXd D = MatrixXd::Zero(A.rows(), B.cols());
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

  b.add(naive_v, "subexpr_nai");
  b.add(recommended_v, "subexpr_rec");
}
