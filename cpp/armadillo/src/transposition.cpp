#include "../lib/transposition.h"

void transposition_nn(const mat& A, const mat& B, mat& C)
{
  C = A * B;
}

void transposition_tn(const mat& A, const mat& B, mat& C)
{
  C = trans(A) * B;
}

void transposition_nt(const mat& A, const mat& B, mat& C)
{
  C = A * trans(B);
}

void transposition_tt(const mat& A, const mat& B, mat& C)
{
  C = trans(A) * trans(B);
}

void bench_transposition(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(size(A));
  std::vector<double> transposition_nn_v(LAMP_REPS);
  std::vector<double> transposition_tn_v(LAMP_REPS);
  std::vector<double> transposition_nt_v(LAMP_REPS);
  std::vector<double> transposition_tt_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, transposition_nn(At, Bt, Ct), transposition_nn_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, transposition_tn(At, Bt, Ct), transposition_tn_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, transposition_nt(At, Bt, Ct), transposition_nt_v[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, transposition_tt(At, Bt, Ct), transposition_tt_v[i]);
  }

  b.add(transposition_nn_v, "tr_nn_implicit");
  b.add(transposition_tn_v, "tr_tn_implicit");
  b.add(transposition_nt_v, "tr_nt_implicit");
  b.add(transposition_tt_v, "tr_tt_implicit");
}
