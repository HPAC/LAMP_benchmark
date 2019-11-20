#include "../lib/properties_solve.h"

void bench_properties_solve(int m, int rhs, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> spd_v(LAMP_REPS);
  std::vector<double> sym_v(LAMP_REPS);
  std::vector<double> tri_v(LAMP_REPS);
  std::vector<double> dia_v(LAMP_REPS);

  dmat B = randn<dmat>(m, rhs);
  dmat C = zeros<dmat>(m, rhs);

  dmat A = randn<dmat>(m, m);
  A = A + trans(A) - diagmat(A) + eye<dmat>(m, m) * m;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  std::cout << "A is SPD   : " << A.is_sympd(1e-5) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {

    BENCHMARK(b, solve(C, A, B, solve_opts::fast), spd_v[i]);
  }

  A = randn<dmat>(m, m);
  A = A + trans(A) - diagmat(A);
  A(0, 0) = -1.0;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  std::cout << "A is SPD   : " << A.is_sympd() << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {

    BENCHMARK(b, solve(C, A, B, solve_opts::fast), sym_v[i]);
  }

  A = randn<dmat>(m, m);
  A = trimatl(A);
  std::cout << "A lower triangular: " << approx_equal(A, trimatl(A), "both", 1e-10, 1e-10) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {

    BENCHMARK(b, solve(C, A, B, solve_opts::fast), tri_v[i]);
  }

  A = randn<dmat>(m, m);
  A = diagmat(A);
  std::cout << "A diagonal: " << approx_equal(A, diagmat(A), "both", 1e-10, 1e-10) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {

    BENCHMARK(b, solve(C, A, B, solve_opts::fast), dia_v[i]);
  }

  b.add(spd_v, "solve_spd");
  b.add(sym_v, "solve_sym");
  b.add(tri_v, "solve_tri");
  b.add(dia_v, "solve_dia");
}
