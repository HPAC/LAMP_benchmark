#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

void dsysv_(const char*, const int*, const int*, const double*, const int*, int*, double*, const int*, double*, const int*, const int*);
void dgemm_(const char*, const char*, const int*, const int*, const int*, const double*, const double*, const int*, const double*, const int*, const double*, double*, const int*);

int main(int argc, char* argv[])
{
  int n, rhs;
  double one = 1.0;
  double minus_one = -1.0;
  int* ipiv;
  double *A, *B, *B_orig, *A_orig, *work;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments: n, rhs\n");
    return (-1);
  } else {
    n = atof(argv[1]);
    rhs = atof(argv[2]);
  }

  for (int it = 0; it < LAMP_REPS; it++) {

    A = (double*)malloc(n * n * sizeof(double));
    work = (double*)malloc(n * n * sizeof(double));
    A_orig = (double*)malloc(n * n * sizeof(double));
    B = (double*)malloc(n * rhs * sizeof(double));
    B_orig = (double*)malloc(n * rhs * sizeof(double));
    ipiv = (int*)malloc(1 * n * sizeof(int));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < n * n; i++)
      A[i] = drand48();
    for (int i = 0; i < n * rhs; i++) {
      B[i] = drand48();
      B_orig[i] = B[i];
    }

    // Create Symmetric Matrix
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (i > j)
          A[i + j * n] = A[j + i * n];
      }
    A[0] = -1.0;
    for (int i = 0; i < n * n; i++) {
      A_orig[i] = A[i];
    }

    /*printf("A = \n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf("%2.5f ", A[i + j * n]);*/
    /*printf("\n");*/
    /*}*/

    int solve_info = 0;
    int lwork = n * n;

    cs_time = cache_scrub();
    dtime = cclock();
    dsysv_("L", &n, &rhs, A, &n, ipiv, B, &n, work, &lwork, &solve_info);
    dtime_save = clock_min_diff(dtime_save, dtime);

    dgemm_("N", "N", &n, &rhs, &n, &one, A_orig, &n, B, &n, &minus_one, B_orig, &n);
    double max_value = abs(B_orig[0]);
    for (int i = 0; i < n * rhs; i++)
      max_value = fmax(fabs(B_orig[i]), max_value);
    if (max_value > 1e-08) {
      printf("Verification failed...\n");
      printf("Max value:  %e\n", max_value);
      printf("Solve info: %d\n", solve_info);
      return (-1);
    }

    free(A);
    free(A_orig);
    free(B);
    free(B_orig);
    free(ipiv);
  };

  printf("solve_sym;%d;%d;%d;%e;%e\n", 0, rhs, n, dtime_save, cs_time);

  return (0);
}
