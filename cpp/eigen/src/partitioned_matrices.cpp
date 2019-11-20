#include "../lib/partitioned_matrices.h"

static void implicit_partitioned(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, MatrixXd& C)
{
  MatrixXd tempA = MatrixXd::Zero(B.rows(), B.cols());
  tempA.block(0, 0, A1.rows(), A1.cols()) = A1;
  tempA.block(A1.rows(), A2.cols(), A2.rows(), A2.cols()) = A2;
  C = tempA.partialPivLu().solve(B);
}

static void explicit_partitioned(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, MatrixXd& C)
{
  C.block(0, 0, A1.rows(), B.cols()) = A1.partialPivLu().solve(B.block(0, 0, A1.rows(), B.cols()));
  C.block(A1.rows(), 0, A2.rows(), B.cols()) = A2.partialPivLu().solve(B.block(A1.rows(), 0, A2.rows(), B.cols()));
}

void bench_partitioned_matrices(const MatrixXd& A1, const MatrixXd& A2, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  MatrixXd C = MatrixXd::Zero(B.rows(), B.cols());

  std::vector<double> implicit_v(LAMP_REPS);
  std::vector<double> explicit_v(LAMP_REPS);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //implicit_partitioned(A1, A2, B, c1);
  //explicit_partitioned(A1, A2, B, c2);
  //std::cout << "Partitioned Matrices equal: " << c1.isApprox(c2, 1e-11) << std::endl;
  //std::cout << "Partitioned Matrices equal: " << (c1 - c2).norm() / c1.norm() << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd A1t = A1;
    MatrixXd A2t = A2;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, implicit_partitioned(A1t, A2t, Bt, Ct), implicit_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd A1t = A1;
    MatrixXd A2t = A2;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, explicit_partitioned(A1t, A2t, Bt, Ct), explicit_v[i]);
  }

  b.add(implicit_v, "compact");
  b.add(explicit_v, "blocked");
}
