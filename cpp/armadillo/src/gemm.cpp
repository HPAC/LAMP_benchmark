#include "../lib/gemm.h"

void gemm_implicit(const mat& A, const mat& B, mat& C)
{
  C = A * B + C;
}

void gemm_implicit_compact(const mat& A, const mat& B, mat& C)
{
  C += A * B;
}

void gemm_implicit_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * B + C;
}

void gemm_implicit_double_coeff(const mat& A, const mat& B, mat& C)
{
  C = 3.0 * A * B + 3.0 * C;
}

void gemm_implicit_noup(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void trmm_implicit_compact(const mat& A, mat& B)
{
  B *= A;
}

void trmm_implicit(const mat& A, mat& B)
{
  B = A * B;
}

void diagmm(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void bench_gemm(const mat& A, const mat& B, const mat& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> impl_gemm(LAMP_REPS);
  std::vector<double> impl_gemm_compact(LAMP_REPS);
  std::vector<double> impl_gemm_noup(LAMP_REPS);
  std::vector<double> impl_gemm_coeff(LAMP_REPS);
  std::vector<double> impl_gemm_double_coeff(LAMP_REPS);

  std::vector<double> impl_gemm_noup_prop(LAMP_REPS);
  std::vector<double> impl_trmm(LAMP_REPS);
  std::vector<double> impl_trmm_compact(LAMP_REPS);
  std::vector<double> impl_diagmm(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, gemm_implicit(At, Bt, Ct), impl_gemm[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, gemm_implicit_compact(At, Bt, Ct), impl_gemm_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, gemm_implicit_noup(At, Bt, Ct), impl_gemm_noup[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, gemm_implicit_coeff(At, Bt, Ct), impl_gemm_coeff[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, gemm_implicit_double_coeff(At, Bt, Ct), impl_gemm_double_coeff[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = randn<dmat>(A.n_rows, A.n_rows);
    dmat Bt = randn<dmat>(A.n_rows, A.n_rows);
    dmat Ct = randn<dmat>(A.n_rows, A.n_rows);

    BENCHMARK(b, gemm_implicit_noup(At, Bt, Ct), impl_gemm_noup_prop[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = trimatl(randn<dmat>(A.n_rows, A.n_rows));
    dmat Bt = randn<dmat>(A.n_rows, A.n_rows);

    BENCHMARK(b, trmm_implicit(At, Bt), impl_trmm[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = trimatl(randn<dmat>(A.n_rows, A.n_rows));
    dmat Bt = randn<dmat>(A.n_rows, A.n_rows);

    BENCHMARK(b, trmm_implicit_compact(At, Bt), impl_trmm_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = diagmat(randn<dmat>(A.n_rows, A.n_rows));
    dmat Bt = randn<dmat>(A.n_rows, A.n_rows);
    dmat Ct = randn<dmat>(A.n_rows, A.n_rows);

    BENCHMARK(b, diagmm(At, Bt, Ct), impl_diagmm[i]);
  }

  b.add(impl_gemm, "gemm_implicit");
  b.add(impl_gemm_compact, "gemm_implicit_compact");
  b.add(impl_gemm_noup, "gemm_implicit_noup");
  b.add(impl_gemm_coeff, "gemm_implicit_coeff");
  b.add(impl_gemm_double_coeff, "gemm_implicit_double_coeff");

  b.add(impl_gemm_noup_prop, "gemm_prop");
  b.add(impl_trmm, "trmm_implicit");
  b.add(impl_trmm_compact, "trmm_implicit_compact");
  b.add(impl_diagmm, "diagmm");
}
