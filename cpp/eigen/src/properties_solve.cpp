#include "../lib/properties_solve.h"

static void solve(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.partialPivLu().solve(B);
}

void bench_properties_solve(int m, int rhs, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;

  std::vector<double> spd_v(LAMP_REPS);
  std::vector<double> sym_v(LAMP_REPS);
  std::vector<double> tri_v(LAMP_REPS);
  std::vector<double> dia_v(LAMP_REPS);

  //MatrixXd c1 = C;
  //MatrixXd c2 = C;
  //naive(A, B, c1);
  //recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << c1.isApprox(c2) << std::endl;
  MatrixXd C = MatrixXd::Random(m, rhs);
  MatrixXd B = MatrixXd::Random(m, rhs);

  // SPD
  MatrixXd A = MatrixXd::Random(m, m);
  A = A.selfadjointView<Eigen::Lower>();
  A += MatrixXd::Identity(m, m) * m;
  std::cout << "A symmetric: " << A.isApprox(A.transpose()) << std::endl;
  Eigen::LLT<Eigen::MatrixXd> lltOfAspd(A); // compute the Cholesky decomposition of A
  if (lltOfAspd.info() == Eigen::NumericalIssue)
    std::cout << "A SPD: False" << std::endl;
  else
    std::cout << "A SPD: True" << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    BENCHMARK(b, solve(A, B, C), spd_v[i]);
  }

  // Symmetric
  A = MatrixXd::Random(m, m);
  A = A.selfadjointView<Eigen::Lower>();
  A(0, 0) = -1.0;
  std::cout << "A symmetric: " << A.isApprox(A.transpose()) << std::endl;
  Eigen::LLT<Eigen::MatrixXd> lltOfAsym(A); // compute the Cholesky decomposition of A
  if (lltOfAsym.info() == Eigen::NumericalIssue)
    std::cout << "A SPD: False" << std::endl;
  else
    std::cout << "A SPD: True" << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    BENCHMARK(b, solve(A, B, C), sym_v[i]);
  }

  // Triangular
  A = MatrixXd::Random(m, m);
  A = A.triangularView<Eigen::Lower>(); // This step creates a full matrix from the view.
  //std::cout << "A triangular: " << A.isApprox(A.triangularView<Eigen::Lower>()) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    BENCHMARK(b, solve(A, B, C), tri_v[i]);
  }

  // Diagonal
  A = MatrixXd::Random(m, m);
  A = A.diagonal().asDiagonal();
  //std::cout << "A diagonal: " << A.isApprox(A.diagonal().asDiagonal()) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    BENCHMARK(b, solve(A, B, C), dia_v[i]);
  }

  b.add(spd_v, "solve_spd");
  b.add(sym_v, "solve_sym");
  b.add(tri_v, "solve_tri");
  b.add(dia_v, "solve_dia");
}
