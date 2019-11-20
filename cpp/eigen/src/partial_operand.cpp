#include "../lib/partial_operand.h"

static void naive_col_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A + B).col(2);
}

static void recommended_col_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A.col(2) + B.col(2);
}

static void naive_col_mult(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = (A * B).col(2);
}

static void naive_ele_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = (A + B)(1, 1);
}

static void recommended_ele_add(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = A(1, 1) + B(1, 1);
}

static void naive_ele_mult(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  double c = (A * B)(1, 1);
}

void bench_partial_operand(const MatrixXd& A, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  MatrixXd C = MatrixXd::Zero(A.rows(), 1);
  std::vector<double> naive_col_add_v(LAMP_REPS);
  std::vector<double> recommended_col_add_v(LAMP_REPS);
  std::vector<double> naive_col_mult_v(LAMP_REPS);

  std::vector<double> naive_ele_add_v(LAMP_REPS);
  std::vector<double> recommended_ele_add_v(LAMP_REPS);
  std::vector<double> naive_ele_mult_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, naive_col_add(At, Bt, Ct), naive_col_add_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, recommended_col_add(At, Bt, Ct), recommended_col_add_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, naive_col_mult(At, Bt, Ct), naive_col_mult_v[i]);
  }

  C = MatrixXd::Zero(1, 1);
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, naive_ele_add(At, Bt, Ct), naive_ele_add_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, recommended_ele_add(At, Bt, Ct), recommended_ele_add_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, naive_ele_mult(At, Bt, Ct), naive_ele_mult_v[i]);
  }

  b.add(naive_col_add_v, "part_op_col_add_nai");
  b.add(recommended_col_add_v, "part_op_col_add_rec");
  b.add(naive_col_mult_v, "part_op_col_mult_nai");

  b.add(naive_ele_add_v, "part_op_ele_add_nai");
  b.add(recommended_ele_add_v, "part_op_ele_add_rec");
  b.add(naive_ele_mult_v, "part_op_ele_mult_nai");
}
