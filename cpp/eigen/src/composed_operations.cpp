#include "../lib/composed_operations.h"

static void naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.inverse() * B;
}

static void recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.partialPivLu().solve(B);
}

void bench_composed_operations(const MatrixXd& A, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  MatrixXd C = MatrixXd::Zero(A.cols(), B.rows());
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);
  std::vector<double> naive_large_v(LAMP_REPS);
  std::vector<double> recommended_large_v(LAMP_REPS);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //naive(A, B, c1);
  //recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << c1.isApprox(c2) << std::endl;

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

  MatrixXd Bl = MatrixXd::Random(B.rows(), 2 * A.rows());
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = Bl;
    MatrixXd Ct = C;

    BENCHMARK(b, naive(At, Bt, Ct), naive_large_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = Bl;
    MatrixXd Ct = C;

    BENCHMARK(b, recommended(At, Bt, Ct), recommended_large_v[i]);
  }

  b.add(naive_v, "solve_nai");
  b.add(recommended_v, "solve_rec");
  b.add(naive_large_v, "solve_large_nai");
  b.add(recommended_large_v, "solve_large_rec");
}
