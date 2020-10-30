#include "../lib/diagonal_elements.h"

static void mult_naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A * B).diagonal();
}

static void naive(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A + B).diagonal();
}

static void recommended(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.diagonal() + B.diagonal();
}

void bench_diagonal_elements(const MatrixXd& A, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  MatrixXd C = MatrixXd::Zero(A.rows(), 1);
  std::vector<double> mult_naive_v(LAMP_REPS);
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, mult_naive(At, Bt, Ct), mult_naive_v[i]);
    MatrixXd test1 = C;
    mult_naive(At, Bt, test1);

    std::chrono::high_resolution_clock::time_point t1, t2;
    t1 = std::chrono::high_resolution_clock::now();
    MatrixXd test2 = At * Bt;
    t2 = std::chrono::high_resolution_clock::now();
    auto time_verification = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

    // std::cout << "Diagonal mult equal: " << test1.isApprox(test2.diagonal(), 1e-11) <<  "Time for multiplication: " << time_verification << std::endl;
    // std::cout << "==========" << std::endl;
    // std::cout << test1 << std::endl;
    // std::cout << "----------" << std::endl;
    // std::cout << test2.diagonal() << std::endl;
    // std::cout << "@@@@@@@@@@"<< std::endl;
  }

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

  b.add(mult_naive_v, "diag_mult_nai");
  b.add(naive_v, "diag_add_nai");
  b.add(recommended_v, "diag_add_rec");
}
