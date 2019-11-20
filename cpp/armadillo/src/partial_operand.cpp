#include "../lib/partial_operand.h"

static void naive_col(const mat& A, const mat& B, mat& C)
{
  //C = (A + B).col(2);
}

static void recommended_col(const mat& A, const mat& B, mat& C)
{
  C = A.col(2) + B.col(2);
}

static void naive_ele(const mat& A, const mat& B, mat& C)
{
  //C = (A + B)(1, 1);
}

static void recommended_ele(const mat& A, const mat& B, mat& C)
{
  C = A(1, 1) + B(1, 1);
}

void bench_partial_operand(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(A.n_rows, 1);
  std::vector<double> naive_col_v(LAMP_REPS);
  std::vector<double> recommended_col_v(LAMP_REPS);
  std::vector<double> naive_ele_v(LAMP_REPS);
  std::vector<double> recommended_ele_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive_col(At, Bt, Ct), naive_col_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, recommended_col(At, Bt, Ct), recommended_col_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive_ele(At, Bt, Ct), naive_ele_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, recommended_ele(At, Bt, Ct), recommended_ele_v[i]);
  }

  // b.add(naive_col_v, "part_op_col_add_nai");
  // b.add(recommended_col_v, "part_op_col_add_rec");
  // b.add(naive_ele_v, "part_op_ele_add_nai");
  // b.add(recommended_ele_v, "part_op_ele_add_rec");
}
