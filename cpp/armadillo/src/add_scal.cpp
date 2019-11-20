#include "../lib/add_scal.h"

static void add(const mat& A, mat& B)
{
  B = A + B;
}

static void scal(mat& A)
{
  A = 3.0 * A;
}

void bench_add_scal(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> add_v(LAMP_REPS);
  std::vector<double> scal_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;

    BENCHMARK(b, add(At, Bt), add_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;

    BENCHMARK(b, scal(At), scal_v[i]);
  }

  b.add(add_v, "add");
  b.add(scal_v, "scal");
}
