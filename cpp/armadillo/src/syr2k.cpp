#include "../lib/syr2k.h"

void syr2k_implicit(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B) + B * trans(A) + C;
}

void syr2k_implicit_compact(const mat& A, const mat& B, mat& C)
{
  C += A * trans(B) + B * trans(A);
}

void syr2k_implicit_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * trans(B) + B * trans(A) + C;
}

void syr2k_implicit_double_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * trans(B) + B * trans(A) + 3.0 * C;
}

void syr2k_implicit_noup(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B) + B * trans(A);
}

void bench_syr2k(const mat& A, const mat& B, const mat& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> impl_syr2k(LAMP_REPS);
  std::vector<double> impl_syr2k_compact(LAMP_REPS);
  std::vector<double> impl_syr2k_noup(LAMP_REPS);
  std::vector<double> impl_syr2k_coeff(LAMP_REPS);
  std::vector<double> impl_syr2k_double_coeff(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, syr2k_implicit(At, Bt, Ct), impl_syr2k[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, syr2k_implicit_compact(At, Bt, Ct), impl_syr2k_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, syr2k_implicit_noup(At, Bt, Ct), impl_syr2k_noup[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, syr2k_implicit_coeff(At, Bt, Ct), impl_syr2k_coeff[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, syr2k_implicit_double_coeff(At, Bt, Ct), impl_syr2k_double_coeff[i]);
  }

  b.add(impl_syr2k, "syr2k_implicit");
  b.add(impl_syr2k_compact, "syr2k_implicit_compact");
  b.add(impl_syr2k_noup, "syr2k_implicit_noup");
  b.add(impl_syr2k_coeff, "syr2k_implicit_coeff");
  b.add(impl_syr2k_double_coeff, "syr2k_implicit_double_coeff");
}
