#include "../lib/partitioned_matrices.h"

static void implicit_partitioned(const mat& A1, const mat& A2, const mat& B, mat& C)
{
  C = solve(join_vert(join_horiz(A1, zeros(A1.n_rows, A1.n_cols)), join_horiz(zeros(A2.n_rows, A2.n_cols), A2)), B, solve_opts::fast);
}

static void explicit_partitioned(const mat& A1, const mat& A2, const mat& B, mat& C)
{
  dmat b1 = B(span(0, A1.n_rows - 1), span(0, B.n_cols - 1));
  dmat b2 = B(span(A1.n_rows, B.n_rows - 1), span(0, B.n_cols - 1));
  C = join_vert(solve(A1, b1, solve_opts::fast), solve(A2, b2, solve_opts::fast));
}

void bench_partitioned_matrices(const mat& A1, const mat& A2, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(B.n_rows, B.n_cols);

  std::vector<double> implicit_v(LAMP_REPS);
  std::vector<double> explicit_v(LAMP_REPS);

  //dmat c1 = C;
  //dmat c2 = C;
  //implicit_partitioned(A1, A2, B, c1);
  //explicit_partitioned(A1, A2, B, c2);
  //std::cout << "Linsolve equal: " << approx_equal(c1, c2, "both", 1e-5, 1e-5) << std::endl;

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat A1t = A1;
    dmat A2t = A2;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, implicit_partitioned(A1t, A2t, Bt, Ct), implicit_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat A1t = A1;
    dmat A2t = A2;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, explicit_partitioned(A1t, A2t, Bt, Ct), explicit_v[i]);
  }

  b.add(implicit_v, "compact");
  b.add(explicit_v, "blocked");
}
